#include <cstring>
#include "../headers/BinaryIO.hpp"
#include "../include/exceptions.hpp"
#include "../include/bin.hpp"
#include "../include/version.hpp"
#undef APIENTRY
#define RYML_SINGLE_HDR_DEFINE_NOW
#include "../ryml/rapidyaml-0.5.0.hpp"

namespace {
	std::vector<uint8_t> decompressBin(std::vector<uint8_t> &inputVector) {
		std::vector<uint8_t> outputVector(sizeof(FuryUtils::Archive::Bin));
		uint8_t *outputBuffer = outputVector.data();
		uint8_t *inputBuffer = inputVector.data();
		uint32_t outputLocation = 0;
		uint32_t inputLocation = 4;
		uint16_t inputSize = (uint16_t)inputVector.size() - 4;
		while (outputLocation < sizeof(FuryUtils::Archive::Bin)) {
			if (inputSize < 2) {
				FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
			}
			uint16_t copySize = inputBuffer[inputLocation++];
			copySize += inputBuffer[inputLocation++] * 256;
			if (copySize == 0) {
				copySize = (uint16_t)sizeof(FuryUtils::Archive::Bin) - outputLocation;
				while (copySize--) {
					outputBuffer[outputLocation++] = 0;
				}
			}
			else if (copySize < 0x7D00) {
				if (copySize > (sizeof(FuryUtils::Archive::Bin) - outputLocation)) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				inputSize -= 2;
				if (copySize > inputSize) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				memcpy(outputBuffer + outputLocation, inputBuffer + inputLocation, copySize);
				outputLocation += copySize;
				inputLocation += copySize;
				inputSize -= copySize;
			}
			else {
				copySize -= 0x7D00;
				if (inputSize < 1) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				uint8_t runByte = inputBuffer[inputLocation++];
				inputSize--;
				if (copySize > (sizeof(FuryUtils::Archive::Bin) - outputLocation)) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				while (copySize--) {
					outputBuffer[outputLocation++] = runByte;
				}
			}
		}
		return outputVector;
	}
	
	void ConvertUncompressed(std::vector<uint8_t> &vector, const FuryUtils::Archive::Bin *bin) {
		std::vector<uint8_t>outputBuffer(sizeof(FuryUtils::Archive::Bin) + 8);
		outputBuffer[0] = 'b';
		outputBuffer[1] = 'y';
		outputBuffer[2] = 't';
		outputBuffer[3] = '4';
		outputBuffer[4] = sizeof(FuryUtils::Archive::Bin) % 256;
		outputBuffer[5] = sizeof(FuryUtils::Archive::Bin) / 256;
		memcpy(outputBuffer.data() + 6, bin, sizeof(FuryUtils::Archive::Bin));
		outputBuffer[outputBuffer.size() - 2] = 0;
		outputBuffer[outputBuffer.size() - 1] = 0;
		outputBuffer.swap(vector);
	}
	
	void ConvertCompressed(std::vector<uint8_t> &vector, const FuryUtils::Archive::Bin *bin) {
		std::vector<uint8_t>outputVector(65535);
		uint8_t *outputBuffer = outputVector.data();
		outputBuffer[0] = 'b';
		outputBuffer[1] = 'y';
		outputBuffer[2] = 't';
		outputBuffer[3] = '4';
		uint16_t outputOffset = 4;
		uint8_t *inputBuffer = (uint8_t *)bin;
		uint16_t inputOffset = 0;
		while (true) {
			uint8_t prevChar = inputBuffer[inputOffset];
			uint8_t prevPrevChar = prevChar++;
			uint16_t seqStart = inputOffset;
			uint16_t runStart = 0;
			// find sequence of literal characters, followed by a run.
			while(inputOffset < sizeof(FuryUtils::Archive::Bin)) {
				uint8_t thisChar;
				if ((thisChar = inputBuffer[inputOffset++]) == prevChar && prevChar == prevPrevChar) {
					runStart = inputOffset - 3;
					while(inputOffset < sizeof(FuryUtils::Archive::Bin)) {
						if (inputBuffer[inputOffset] != prevChar) {
							break;
						}
						inputOffset++;
					}
					break;
				}
				prevPrevChar = prevChar;
				prevChar = thisChar;
			}
			uint16_t length = inputOffset - seqStart;
			if (!length) {
				break;
			}
			if (runStart == seqStart) { // All run, no literals.
				runStart++;
			}
			if (!runStart) {
				runStart = inputOffset;
			}
			uint16_t seqLength = runStart - seqStart;
			uint16_t runLength = inputOffset - runStart;
			outputBuffer[outputOffset++] = seqLength % 256;
			outputBuffer[outputOffset++] = seqLength / 256;
			memcpy(outputBuffer + outputOffset, inputBuffer + seqStart, seqLength);
			outputOffset += (seqLength);
			if (runStart && runLength) {
				outputBuffer[outputOffset++] = runLength % 256;
				outputBuffer[outputOffset++] = 0x7D + runLength / 256;
				outputBuffer[outputOffset++] = inputBuffer[runStart];
			}
		}
		outputBuffer[outputOffset++] = 0;
		outputBuffer[outputOffset++] = 0;
		outputVector.resize(outputOffset);
		vector.swap(outputVector);
	}
	
	void ConvertYaml(std::vector<uint8_t> &vector, const FuryUtils::Archive::Bin *bin) {

		ryml::NodeRef ff;
		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		
		root |= ryml::MAP;
		ff = root["FuryOfTheFurries"];
		ff |= ryml::MAP;
		
		ff["version"] << std::string(Version_string());
		ff["mapWidth"] << bin->mapWidth;
		ff["mapHeight"] << bin->mapHeight;
		ff["time"] << bin->time;
		
		{
			ryml::NodeRef map = ff["map"];
			map |= ryml::SEQ;
			for(uint16_t y = 0; y < bin->mapHeight; y++) {
				ryml::NodeRef row = map.append_child();
				row |= ryml::MAP;
				row["row"] << (y + 1);
				ryml::NodeRef rowSeq = row["tiles"];
				rowSeq |= ryml::SEQ;
				bool skipX = false;
				for(uint16_t x = 0; x < bin->mapWidth; x++) {
					if (bin->map[y][x].x + bin->map[y][x].y) {
						ryml::NodeRef tile = rowSeq.append_child();
						tile |= ryml::MAP;
						if (skipX) {
							skipX = false;
							tile["column"] << (x + 1);
						}
						tile["xy"] << (std::string(1, 'A' + (bin->map[y][x].x % 26)) + std::string(1, 'A' + (bin->map[y][x].y % 26)));
					}
					else {
						skipX = true;
					}
				}
			}
		}
		ff["decorFile"] << (1 + bin->decFile);
		ff["spriteFile"] << (1 + bin->spriteMap);
		ff["startLeft"] << bin->startLeft;
		ff["startTop"] << bin->startTop;
		ff["foreground"] << bin->foregroundPalette;
		ff["water"] << bin->waterPalette;
		ff["air"] << bin->airPalette;
		ff["motes"] << bin->motePalette;
		{
			ryml::NodeRef exits = ff["exits"];
			exits |= ryml::SEQ;
			bool skip = false;
			for(uint8_t i = 0; i < 5; i++) {
				if (bin->exits[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef exit = exits.append_child();
					exit |= ryml::MAP;
					if (skip) {
						skip = false;
						exit["index"] << (i + 1);
					}
					exit["left"] << bin->exits[i].left;
					exit["top"] << bin->exits[i].top;
					exit["destination"] << (1 + bin->exits[i].destination & 0x7FFF);
					if (bin->exits[i].destination & 0x8000) {
						ryml::NodeRef options = exit["options"];
						options |= ryml::SEQ;
						options |= ryml::_WIP_STYLE_FLOW_SL;
						options.append_child() << "bonus";
					}
					if (bin->exitReturns[i].left != 0xFFFF) {
						exit["returnLeft"] << bin->exitReturns[i].left;
						exit["returnTop"] << bin->exitReturns[i].top;
					}
					if (bin->exitGraphic[i] == 1) {
						ryml::NodeRef options = exit["options"];
						options |= ryml::SEQ;
						options |= ryml::_WIP_STYLE_FLOW_SL;
						options.append_child() << "smooth";
					}
				}
			}
			if (exits.num_children() == 0) {
				ff.remove_child(exits);
			}
		}
		{
			ryml::NodeRef water = ff["water1"];
			water |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->water1[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = water.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->water1[i].left;
					item["top"] << bin->water1[i].top;
					item["right"] << bin->water1[i].right;
					item["bottom"] << bin->water1[i].bottom;
				}
			}
			if (water.num_children() == 0) {
				ff.remove_child(water);
			}
		}
		{
			ryml::NodeRef water = ff["water2"];
			water |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->water2[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = water.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->water2[i].left;
					item["top"] << bin->water2[i].top;
					item["right"] << bin->water2[i].right;
					item["bottom"] << bin->water2[i].bottom;
				}
			}
			if (water.num_children() == 0) {
				ff.remove_child(water);
			}
		}
		{
			ryml::NodeRef teleport = ff["teleport"];
			teleport |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->teleports[i].srcX == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = teleport.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["sourceX"] << bin->teleports[i].srcX;
					item["sourceY"] << bin->teleports[i].srcY;
					item["destX"] << bin->teleports[i].destX;
					item["destY"] << bin->teleports[i].destY;
				}
			}
			if (teleport.num_children() == 0) {
				ff.remove_child(teleport);
			}
		}
		{
			ryml::NodeRef nonstick = ff["nonStick"];
			nonstick |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->nonstick[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = nonstick.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->nonstick[i].left;
					item["top"] << bin->nonstick[i].top;
					item["right"] << bin->nonstick[i].right;
					item["bottom"] << bin->nonstick[i].bottom;
				}
			}
			if (nonstick.num_children() == 0) {
				ff.remove_child(nonstick);
			}
		}
		{
			ryml::NodeRef acid = ff["acid"];
			acid |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->acid[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = acid.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->acid[i].left;
					item["top"] << bin->acid[i].top;
					item["right"] << bin->acid[i].right;
					item["bottom"] << bin->acid[i].bottom;
				}
			}
			if (acid.num_children() == 0) {
				ff.remove_child(acid);
			}
		}
		{
			ryml::NodeRef danger = ff["danger"];
			danger |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 20; i++) {
				if (bin->danger[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = danger.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->danger[i].left;
					item["top"] << bin->danger[i].top;
					item["right"] << bin->danger[i].right;
					item["bottom"] << bin->danger[i].bottom;
				}
			}
			if (danger.num_children() == 0) {
				ff.remove_child(danger);
			}
		}
		/// TODO Sprites
		{
			ryml::NodeRef start = ff["start"];
			start |= ryml::SEQ;
			start |= ryml::_WIP_STYLE_FLOW_SL;
			if (bin->blue) start.append_child() << "blue";
			if (bin->green) start.append_child() << "green";
			if (bin->red) start.append_child() << "red";
			if (bin->yellow) start.append_child() << "yellow";
		}
		{
			ryml::NodeRef field = ff["blueFields"];
			field |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->blueFields[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = field.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->blueFields[i].left;
					item["top"] << bin->blueFields[i].top;
					item["right"] << bin->blueFields[i].right;
					item["bottom"] << bin->blueFields[i].bottom;
				}
			}
			if (field.num_children() == 0) {
				ff.remove_child(field);
			}
		}
		{
			ryml::NodeRef field = ff["greenFields"];
			field |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->greenFields[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = field.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->greenFields[i].left;
					item["top"] << bin->greenFields[i].top;
					item["right"] << bin->greenFields[i].right;
					item["bottom"] << bin->greenFields[i].bottom;
				}
			}
			if (field.num_children() == 0) {
				ff.remove_child(field);
			}
		}
		{
			ryml::NodeRef field = ff["redFields"];
			field |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->redFields[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = field.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->redFields[i].left;
					item["top"] << bin->redFields[i].top;
					item["right"] << bin->redFields[i].right;
					item["bottom"] << bin->redFields[i].bottom;
				}
			}
			if (field.num_children() == 0) {
				ff.remove_child(field);
			}
		}
		{
			ryml::NodeRef field = ff["yellowFields"];
			field |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->yellowFields[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = field.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->yellowFields[i].left;
					item["top"] << bin->yellowFields[i].top;
					item["right"] << bin->yellowFields[i].right;
					item["bottom"] << bin->yellowFields[i].bottom;
				}
			}
			if (field.num_children() == 0) {
				ff.remove_child(field);
			}
		}
		
		ryml::csubstr getLength = ryml::emit_yaml(tree, tree.root_id(), ryml::substr{}, false);
		std::vector<char> charVec(getLength.len);
		ryml::emit_yaml(tree, tree.root_id(), ryml::to_substr(charVec), true);
		std::vector<uint8_t> outputVec((uint8_t *)charVec.data(), (uint8_t *)charVec.data() + charVec.size());
		vector.swap(outputVec);
	}
}

namespace FuryUtils {
	namespace Archive {

		Bin::Bin() {}
		Bin::Bin(std::vector<uint8_t> &inputBuffer) {
			if (inputBuffer.size() < 6) {
				Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_BIN_BUFFER_TOO_SMALL);
			}
			if (inputBuffer[0] == 'b' &&
				inputBuffer[1] == 'y' &&
				inputBuffer[2] == 't') {
				if (inputBuffer[4] == 0xAE &&
					inputBuffer[5] == 0x63 &&
					inputBuffer.size() == 6 + sizeof(Bin)) {
					memcpy(this, inputBuffer.data() + 6, sizeof(Bin));
				}
				else {
					std::vector<uint8_t> decompressionBuffer = decompressBin(inputBuffer);
					memcpy(this, decompressionBuffer.data(), sizeof(Bin));
				}
			}
			else if (inputBuffer[0] == 'F' &&
				inputBuffer[1] == 'u' &&
				inputBuffer[2] == 'r' &&
				inputBuffer[3] == 'y') {
				ParseYaml(inputBuffer);
			}
			else {
				Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_BIN_UNRECOGNISED_FORMAT);
			}
		}
		
		void CheckNodeIsMap(ryml::ConstNodeRef &ref) {
			if (ref.is_map()) return;
			Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_BIN_INVALID_YAML);
		}
		
		void CheckNodeIsSeq(ryml::ConstNodeRef &ref) {
			if (ref.is_seq()) return;
			Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_BIN_INVALID_YAML);
		}
		
		void CheckNodeIsVal(ryml::ConstNodeRef &ref) {
			if (ref.is_val()) return;
			Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_BIN_INVALID_YAML);
		}
		
		void Bin::ParseYaml(std::vector<uint8_t> &inputBuffer) {
			
			std::vector<char> charBuf(inputBuffer.data(), inputBuffer.data() + inputBuffer.size() + 1);
			charBuf[charBuf.size() - 1] = 0;
			
			ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(charBuf));
			ryml::ConstNodeRef root = tree.rootref();
			CheckNodeIsMap(root);
			ryml::ConstNodeRef ff = tree["FuryOfTheFurries"];
			CheckNodeIsMap(ff);
			ryml::ConstNodeRef ref;
			if (ff.has_child("mapWidth")) {
				ref = ff["mapWidth"];
				if (ref.is_keyval()) ref >> this->mapWidth;
			}
			if (ff.has_child("mapHeight")) {
				ref = ff["mapHeight"];
				if (ref.is_keyval()) ref >> this->mapHeight;
			}
			if (ff.has_child("time")) {
				ref = ff["time"];
				if (ref.is_keyval()) ref >> this->time;
			}
			if (ff.has_child("decorFile")) {
				ref = ff["decorFile"];
				if (ref.is_keyval()) {
					ref >> this->decFile;
					this->decFile--;
				}
			}
			if (ff.has_child("decorFile")) {
				ref = ff["decorFile"];
				if (ref.is_keyval()) {
					ref >> this->decFile;
					this->decFile--;
				}
			}
			if (ff.has_child("spriteFile")) {
				ref = ff["spriteFile"];
				if (ref.is_keyval()) {
					ref >> this->spriteMap;
					this->spriteMap--;
				}
			}
			if (ff.has_child("startLeft")) {
				ref = ff["startLeft"];
				if (ref.is_keyval()) ref >> this->startLeft;
			}
			if (ff.has_child("startTop")) {
				ref = ff["startTop"];
				if (ref.is_keyval()) ref >> this->startTop;
			}
			if (ff.has_child("foreground")) {
				ref = ff["foreground"];
				if (ref.is_keyval()) ref >> this->foregroundPalette;
			}
			if (ff.has_child("water")) {
				ref = ff["water"];
				if (ref.is_keyval()) ref >> this->waterPalette;
			}
			if (ff.has_child("air")) {
				ref = ff["air"];
				if (ref.is_keyval()) ref >> this->airPalette;
			}
			if (ff.has_child("motes")) {
				ref = ff["motes"];
				if (ref.is_keyval()) ref >> this->motePalette;
			}
			if (ff.has_child("map")) {
				ref = ff["map"];
				CheckNodeIsSeq(ref);
				uint8_t y = 0;
				for(ryml::ConstNodeRef row : ref.children()) {
					y++;
					CheckNodeIsMap(row);
					if (row.has_child("row")) {
						ref = row["row"];
						if (ref.is_keyval()) ref >> y;
					}
					if (y > 51) break;
					if (row.has_child("tiles")) {
						ref = row["tiles"];
						CheckNodeIsSeq(ref);
						uint8_t x = 0;
						for(ryml::ConstNodeRef tile : ref.children()) {
							x++;
							CheckNodeIsMap(tile);
							if (tile.has_child("column")) {
								ref = tile["column"];
								if (ref.is_keyval()) ref >> x;
							}
							if (x > 78) break;
							if (tile.has_child("xy")) {
								ref = tile["xy"];
								if (ref.is_keyval()) {
									if (ref.val().len == 2) {
										this->map[y-1][x-1].x = ref.val()[0] - 'A';
										this->map[y-1][x-1].y = ref.val()[1] - 'A';
									}
								}
							}
						}
					}
				}
			}
			
			if (ff.has_child("exits")) {
				ref = ff["exits"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->exits[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->exits[i-1].top;
					}
					if (n.has_child("destination")) {
						ref = n["destination"];
						if (ref.is_keyval()) {
							ref >> this->exits[i-1].destination;
							this->exits[i-1].destination--;
						}
					}
					if (n.has_child("returnLeft")) {
						ref = n["returnLeft"];
						if (ref.is_keyval()) ref >> this->exitReturns[i-1].left;
					}
					if (n.has_child("returnRight")) {
						ref = n["returnTop"];
						if (ref.is_keyval()) ref >> this->exitReturns[i-1].top;
					}
					if (n.has_child("options")) {
						ref = n["options"];
						if (ref.is_seq()) {
							for(ryml::ConstNodeRef m : ref.children()) {
								CheckNodeIsVal(m);
								if (m.val().begins_with("bonus"))
									this->exits[i-1].destination |= 0x8000;
								if (m.val().begins_with("smooth"))
									this->exitGraphic[i-1] = 1;
							}
						}
					}
				}
			}
			if (ff.has_child("water1")) {
				ref = ff["water1"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->water1[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->water1[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->water1[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->water1[i-1].bottom;
					}
				}
			}
			if (ff.has_child("water2")) {
				ref = ff["water2"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->water2[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->water2[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->water2[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->water2[i-1].bottom;
					}
				}
			}
			if (ff.has_child("teleport")) {
				ref = ff["teleport"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("sourceX")) {
						ref = n["sourceX"];
						if (ref.is_keyval()) ref >> this->teleports[i-1].srcX;
					}
					if (n.has_child("sourceY")) {
						ref = n["sourceY"];
						if (ref.is_keyval()) ref >> this->teleports[i-1].srcY;
					}
					if (n.has_child("destX")) {
						ref = n["destX"];
						if (ref.is_keyval()) ref >> this->teleports[i-1].destX;
					}
					if (n.has_child("destY")) {
						ref = n["destY"];
						if (ref.is_keyval()) ref >> this->teleports[i-1].destY;
					}
				}
			}
			if (ff.has_child("nonStick")) {
				ref = ff["nonStick"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].bottom;
					}
				}
			}
			if (ff.has_child("nonStick")) {
				ref = ff["nonStick"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->nonstick[i-1].bottom;
					}
				}
			}
			if (ff.has_child("acid")) {
				ref = ff["acid"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->acid[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->acid[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->acid[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->acid[i-1].bottom;
					}
				}
			}
			if (ff.has_child("danger")) {
				ref = ff["danger"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 20) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->danger[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->danger[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->danger[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->danger[i-1].bottom;
					}
				}
			}
			if (ff.has_child("start")) {
				ref = ff["start"];
				if (ref.is_seq())
				CheckNodeIsSeq(ref);
				for(ryml::ConstNodeRef m : ref.children()) {
					CheckNodeIsVal(m);
					if (m.val().begins_with("blue")) this->blue = 1;
					if (m.val().begins_with("green")) this->green = 1;
					if (m.val().begins_with("red")) this->red = 1;
					if (m.val().begins_with("yellow")) this->yellow = 1;
				}
			}
			if (ff.has_child("blueFields")) {
				ref = ff["blueFields"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->blueFields[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->blueFields[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->blueFields[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->blueFields[i-1].bottom;
					}
				}
			}
			if (ff.has_child("greenFields")) {
				ref = ff["greenFields"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->greenFields[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->greenFields[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->greenFields[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->greenFields[i-1].bottom;
					}
				}
			}
			if (ff.has_child("redFields")) {
				ref = ff["redFields"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->redFields[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->redFields[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->redFields[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->redFields[i-1].bottom;
					}
				}
			}
			if (ff.has_child("yellowFields")) {
				ref = ff["yellowFields"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 5) break;
					if (n.has_child("left")) {
						ref = n["left"];
						if (ref.is_keyval()) ref >> this->yellowFields[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->yellowFields[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->yellowFields[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->yellowFields[i-1].bottom;
					}
				}
			}
			
		}
		void Bin::Convert(std::vector<uint8_t> &buffer, Bin::ConversionType type) {
			switch (type) {
				case Uncompressed:
					ConvertUncompressed(buffer, this);
					break;
				case Compressed:
					ConvertCompressed(buffer, this);
					break;
				case Yaml:
					ConvertYaml(buffer, this);
					break;
				default: 
					Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_BIN_UNRECOGNISED_FORMAT);
			}
		}
	}
}