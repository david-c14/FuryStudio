#include <cstring>
#include "../headers/BinaryIO.hpp"
#include "../include/exceptions.hpp"
#include "../include/bin.hpp"
#undef APIENTRY
#define RYML_SINGLE_HDR_DEFINE_NOW
#include "../ryml/rapidyaml-0.5.0.hpp"
#include "version.hpp"

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
	
	struct YamlErrorHandler {
		void on_error(const char* msg, size_t len, ryml::Location loc) {
			FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::INVALID_FORMAT, ryml::formatrs<std::string>("YAML PARSING ERROR {}", ryml::csubstr(msg, len)));
		}
		
		ryml::Callbacks callbacks() {
			return ryml::Callbacks(this, nullptr, nullptr, YamlErrorHandler::s_error);
		}
		
		static void s_error(const char *msg, size_t len, ryml::Location loc, void *this_) {
			return ((YamlErrorHandler*)this_)->on_error(msg, len, loc);
		}
		
		YamlErrorHandler() : defaults(ryml::get_callbacks()) {}
		ryml::Callbacks defaults;
		
		bool set = false;
		
		void SetCallbacks() {
			if (!set) {
				set = true;
				ryml::set_callbacks(this->callbacks());
			}
		}
	};
	
	YamlErrorHandler yamlErrorHandler;
	
	void ConvertYaml(std::vector<uint8_t> &vector, const FuryUtils::Archive::Bin *bin, std::string comment) {
		
		const std::string uri("# yaml-language-server: $schema=https://schema.submarine.org.uk/carbon14/FuryStudio/2023-07/FuryOfTheFurries.json\n");

		ryml::NodeRef ff;
		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		
		root |= ryml::MAP;
		ff = root["FuryOfTheFurries"];
		ff |= ryml::MAP;
		ff["version"] << std::string(UTILS_VER);
		{
			if (comment.c_str()[0]) {
				ff["comment"] << comment.c_str();
			}
		}
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
				if (rowSeq.num_children() == 0) {
					map.remove_child(row);
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
		{
			ryml::NodeRef current = ff["currents"];
			current |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 5; i++) {
				if (bin->currents[i].left == 0xFFFF) {
					skip = true;
				}
				else {
					ryml::NodeRef item = current.append_child();
					item |= ryml::MAP;
					if (skip) {
						skip = false;
						item["index"] << (i + 1);
					}
					item["left"] << bin->currents[i].left;
					item["top"] << bin->currents[i].top;
					item["right"] << bin->currents[i].right;
					item["bottom"] << bin->currents[i].bottom;
					ryml::NodeRef options = item["options"];
					options |= ryml::SEQ;
					options |= ryml::_WIP_STYLE_FLOW_SL;
					if ((bin->currents[i].flags & 0x3) == 0)
						options.append_child() << "down";
					if ((bin->currents[i].flags & 0x3) == 1)
						options.append_child() << "right";
					if ((bin->currents[i].flags & 0x3) == 2)
						options.append_child() << "up";
					if ((bin->currents[i].flags & 0x3) == 3)
						options.append_child() << "left";
					if (bin->currents[i].flags & 0x4) 
						options.append_child() << "strong";
					else
						options.append_child() << "weak";
					if (bin->currents[i].flags & 0x8)
						options.append_child() << "motes";
				}
			}
			if (current.num_children() == 0) {
				ff.remove_child(current);
			}
		}
		{
			ryml::NodeRef sprites = ff["sprites"];
			sprites |= ryml::SEQ;
			bool skip = false;
			for (uint8_t i = 0; i < 10; i++) {
				ryml::NodeRef sprite = sprites.append_child();
				sprite |= ryml::MAP;
				if (skip) {
					skip = false;
					sprite["index"] << (i + 1);
				}
				if (bin->sprites[i].layer == 0)
					sprite["depth"] << "middle";
				else if (bin->sprites[i].layer == 1)
					sprite["depth"] << "behind";
				else if (bin->sprites[i].layer == 2)
					sprite["depth"] << "front";
				if (bin->sprites[i].malevolence) {
					ryml::NodeRef kills = sprite["kills"];
					kills |= ryml::SEQ;
					kills |= ryml::_WIP_STYLE_FLOW_SL;
					if (bin->sprites[i].malevolence & 0x01)
						kills.append_child() << "red";
					if (bin->sprites[i].malevolence & 0x02)
						kills.append_child() << "yellow";
					if (bin->sprites[i].malevolence & 0x04)
						kills.append_child() << "green";
					if (bin->sprites[i].malevolence & 0x08)
						kills.append_child() << "blue";
				}
				if (bin->sprites[i].mask)
					sprite["mask"] << "true";
				if (bin->sprites[i].cleanUp)
					sprite["cleanUp"] << "true";
				sprite["strength"] << bin->sprites[i].strength;
				sprite["blast"] << bin->sprites[i].blastArea;
				if (bin->sprites[i].active)
					sprite["active"] << "true";
				if (bin->sprites[i].furryEntryRegion.left != 0xFFFF) {
					ryml::NodeRef item = sprite["entryRegion"];
					item |= ryml::MAP;
					item["left"] << bin->sprites[i].furryEntryRegion.left;
					item["top"] << bin->sprites[i].furryEntryRegion.top;
					item["right"] << bin->sprites[i].furryEntryRegion.right;
					item["bottom"] << bin->sprites[i].furryEntryRegion.bottom;
				}
				if (bin->sprites[i].furryExitRegion.left != 0xFFFF) {
					ryml::NodeRef item = sprite["exitRegion"];
					item |= ryml::MAP;
					item["left"] << bin->sprites[i].furryExitRegion.left;
					item["top"] << bin->sprites[i].furryExitRegion.top;
					item["right"] << bin->sprites[i].furryExitRegion.right;
					item["bottom"] << bin->sprites[i].furryExitRegion.bottom;
				}
				if (bin->sprites[i].fireRate)
					sprite["fireRate"] << bin->sprites[i].fireRate;
				if (bin->sprites[i].fireType) {
					if (bin->sprites[i].fireType == 1)
						sprite["fireStyle"] << "slow";
					if (bin->sprites[i].fireType == 2)
						sprite["fireStyle"] << "right";
					if (bin->sprites[i].fireType == 3)
						sprite["fireStyle"] << "left";
					if (bin->sprites[i].fireType == 4)
						sprite["fireStyle"] << "medium";
					if (bin->sprites[i].fireType == 5)
						sprite["fireStyle"] << "fast";
				}
				{
					ryml::NodeRef states = sprite["states"];
					states |= ryml::SEQ;
					bool skip2 = false;
					for (uint8_t j = 0; j < 10; j++) {
						if (bin->sprites[i].states[j].left == 0xFFFF) { // reason for skipping
							skip2 = true;
						}	
						else {
							ryml::NodeRef state = states.append_child();
							state |= ryml::MAP;
							if (skip2) {
								skip2 = false;
								state["index"] << (j + 1);
							}
							state["left"] << bin->sprites[i].states[j].left;
							state["top"] << bin->sprites[i].states[j].top;
							state["movementTarget"] << (1 + bin->sprites[i].states[j].destState);
							if (bin->sprites[i].states[j].speed)
								state["movementSpeed"] << bin->sprites[i].states[j].speed;
							if (bin->sprites[i].states[j].movementType == 0) 
								state["movementStyle"] << "h/v";
							else if (bin->sprites[i].states[j].movementType == 1) 
								state["movementStyle"] << "diagonal";
							else if (bin->sprites[i].states[j].movementType == 2) 
								state["movementStyle"] << "vertical";
							else if (bin->sprites[i].states[j].movementType == 3) 
								state["movementStyle"] << "horizontal";
							else if (bin->sprites[i].states[j].movementType == 4) 
								state["movementStyle"] << "track";
							else if (bin->sprites[i].states[j].movementType == 5) 
								state["movementStyle"] << "fast";
							else if (bin->sprites[i].states[j].movementType == 6) 
								state["movementStyle"] << "none";
							if (bin->sprites[i].states[j].gravity)
								state["gravity"] << "true";
							if (bin->sprites[i].states[j].current) {
								ryml::NodeRef current = state["current"];
								current |= ryml::MAP;
								current["index"] << (1 + (bin->sprites[i].states[j].current & 0xF));
								if (bin->sprites[i].states[j].current & 0x10)
									current["change"] << "off";
								if (bin->sprites[i].states[j].current & 0x20)
									current["change"] << "on";
							}
							if (bin->sprites[i].states[j].activateSprite != 0xFFFF)
								state["otherSprite"] << (1 + bin->sprites[i].states[j].activateSprite);
							if (bin->sprites[i].states[j].entryTrigger.left != 0xFFFF) {
								ryml::NodeRef trigger = state["furryEntryRegion"];
								trigger |= ryml::MAP;
								trigger["index"] << (1 + bin->sprites[i].states[j].entryTrigger.state);
								trigger["left"] << bin->sprites[i].states[j].entryTrigger.left;
								trigger["top"] << bin->sprites[i].states[j].entryTrigger.top;
								trigger["right"] << bin->sprites[i].states[j].entryTrigger.right;
								trigger["bottom"] << bin->sprites[i].states[j].entryTrigger.bottom;
							}
							if (bin->sprites[i].states[j].exitTrigger.left != 0xFFFF) {
								ryml::NodeRef trigger = state["furryExitRegion"];
								trigger |= ryml::MAP;
								trigger["index"] << (1 + bin->sprites[i].states[j].exitTrigger.state);
								trigger["left"] << bin->sprites[i].states[j].exitTrigger.left;
								trigger["top"] << bin->sprites[i].states[j].exitTrigger.top;
								trigger["right"] << bin->sprites[i].states[j].exitTrigger.right;
								trigger["bottom"] << bin->sprites[i].states[j].exitTrigger.bottom;
							}
							if (bin->sprites[i].states[j].spriteEntryTrigger.left != 0xFFFF) {
								ryml::NodeRef trigger = state["spriteEntryRegion"];
								trigger |= ryml::MAP;
								trigger["index"] << (1 + bin->sprites[i].states[j].spriteEntryTrigger.state);
								trigger["left"] << bin->sprites[i].states[j].spriteEntryTrigger.left;
								trigger["top"] << bin->sprites[i].states[j].spriteEntryTrigger.top;
								trigger["right"] << bin->sprites[i].states[j].spriteEntryTrigger.right;
								trigger["bottom"] << bin->sprites[i].states[j].spriteEntryTrigger.bottom;
							}
							if (bin->sprites[i].states[j].spriteExitTrigger.left != 0xFFFF) {
								ryml::NodeRef trigger = state["spriteExitRegion"];
								trigger |= ryml::MAP;
								trigger["index"] << (1 + bin->sprites[i].states[j].spriteExitTrigger.state);
								trigger["left"] << bin->sprites[i].states[j].spriteExitTrigger.left;
								trigger["top"] << bin->sprites[i].states[j].spriteExitTrigger.top;
								trigger["right"] << bin->sprites[i].states[j].spriteExitTrigger.right;
								trigger["bottom"] << bin->sprites[i].states[j].spriteExitTrigger.bottom;
							}
							if (bin->sprites[i].states[j].destroy)
								state["destroy"] << "true";
							if (bin->sprites[i].states[j].bounce)
								state["bounce"] << "true";
							if (bin->sprites[i].states[j].emptyWater.speed) {
								ryml::NodeRef water = state["empty"];
								water |= ryml::MAP;
								water["index"] << (1 + (bin->sprites[i].states[j].emptyWater.region));
								water["speed"] << bin->sprites[i].states[j].emptyWater.speed;
							}
							if (bin->sprites[i].states[j].fillWater.speed) {
								ryml::NodeRef water = state["fill"];
								water |= ryml::MAP;
								water["index"] << (1 + (bin->sprites[i].states[j].fillWater.region));
								water["speed"] << bin->sprites[i].states[j].fillWater.speed;
							}
							if (bin->sprites[i].states[j].waterTriggerLeft != 0xFFFF) {
								ryml::NodeRef trigger = state["waterChangeRegion"];
								trigger |= ryml::MAP;
								trigger["index"] << (1 + bin->sprites[i].states[j].destWaterState);
								trigger["left"] << bin->sprites[i].states[j].waterTriggerLeft;
								trigger["top"] << bin->sprites[i].states[j].waterTriggerTop;
								trigger["right"] << bin->sprites[i].states[j].waterTriggerRight;
								trigger["bottom"] << bin->sprites[i].states[j].waterTriggerBottom;
							}
							{
								ryml::NodeRef anim = state["animation"];
								anim |= ryml::MAP;
								ryml::NodeRef frames = anim["frames"];
								frames |= ryml::SEQ;
								for (uint8_t k = 0; k < 10; k++) {
									if (bin->sprites[i].states[j].frames[k].left == 0xFFFF) {
										break;
									}
									ryml::NodeRef frame = frames.append_child();
									frame |= ryml::MAP;
									frame["left"] << bin->sprites[i].states[j].frames[k].left;
									frame["top"] << bin->sprites[i].states[j].frames[k].top;
									frame["right"] << bin->sprites[i].states[j].frames[k].right;
									frame["bottom"] << bin->sprites[i].states[j].frames[k].bottom;
								}
								if (frames.num_children() == 0)
									anim.remove_child(frames);
								anim["speed"] << bin->sprites[i].states[j].animationSpeed;
								if (bin->sprites[i].states[j].cycle)
									anim["repeat"] << "true";
								anim["count"] << bin->sprites[i].states[j].cycleCount;
								anim["index"] << (1 + bin->sprites[i].states[j].animationTriggerState);
							}
						}
					}
					if (states.num_children() == 0) {
						sprites.remove_child(sprite);
						skip = true;
					}
				}
			}
			if (sprites.num_children() == 0) {
				ff.remove_child(sprites);
			}
		}
		
		ryml::csubstr getLength = ryml::emit_yaml(tree, tree.root_id(), ryml::substr{}, false);
		std::vector<char> charVec(getLength.len);
		ryml::emit_yaml(tree, tree.root_id(), ryml::to_substr(charVec), true);
		std::copy( uri.begin(), uri.end(), std::inserter(charVec, charVec.begin()));
		std::vector<uint8_t> outputVec((uint8_t *)charVec.data(), (uint8_t *)charVec.data() + charVec.size());
		vector.swap(outputVec);
	}
}

namespace FuryUtils {
	namespace Archive {
		
		Bin::Bin() {
			yamlErrorHandler.SetCallbacks();
		}
		Bin::Bin(std::vector<uint8_t> &inputBuffer) {
			yamlErrorHandler.SetCallbacks();
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
			else if (inputBuffer[0] == '#' &&
				inputBuffer[1] == ' ' &&
				inputBuffer[2] == 'y' &&
				inputBuffer[3] == 'a' &&
				inputBuffer[4] == 'm' &&
				inputBuffer[5] == 'l') {
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
			if (ff.has_child("comment")) {
				ref = ff["comment"];
				if (ref.is_keyval()) {
					std::string comment;
					ref >> comment;
					SetComment(comment);
				}
			}
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
					if (n.has_child("returnTop")) {
						ref = n["returnTop"];
						if (ref.is_keyval()) ref >> this->exitReturns[i-1].top;
					}
					if (n.has_child("options")) {
						ref = n["options"];
						if (ref.is_seq()) {
							for(ryml::ConstNodeRef m : ref.children()) {
								CheckNodeIsVal(m);
								if (m.val().begins_with("bonus")) this->exits[i-1].destination |= 0x8000;
								if (m.val().begins_with("smooth")) this->exitGraphic[i-1] = 1;
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
			if (ff.has_child("currents")) {
				ref = ff["currents"];
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
						if (ref.is_keyval()) ref >> this->currents[i-1].left;
					}
					if (n.has_child("top")) {
						ref = n["top"];
						if (ref.is_keyval()) ref >> this->currents[i-1].top;
					}
					if (n.has_child("right")) {
						ref = n["right"];
						if (ref.is_keyval()) ref >> this->currents[i-1].right;
					}
					if (n.has_child("bottom")) {
						ref = n["bottom"];
						if (ref.is_keyval()) ref >> this->currents[i-1].bottom;
					}
					if (n.has_child("options")) {
						ref = n["options"];
						if (ref.is_seq()) {
							for(ryml::ConstNodeRef m : ref.children()) {
								CheckNodeIsVal(m);
								if (m.val().begins_with("down")) this->currents[i-1].flags = 0;
								if (m.val().begins_with("right")) this->currents[i-1].flags = 1;
								if (m.val().begins_with("up")) this->currents[i-1].flags = 2;
								if (m.val().begins_with("left")) this->currents[i-1].flags = 3;
								if (m.val().begins_with("strong")) this->currents[i-1].flags |= 0x4;
								if (m.val().begins_with("motes")) this->currents[i-1].flags |= 0x8;
							}
						}
					}
				}
			}
			if (ff.has_child("sprites")) {
				ref = ff["sprites"];
				CheckNodeIsSeq(ref);
				uint8_t i = 0;
				for(ryml::ConstNodeRef n : ref.children()) {
					i++;
					if (n.has_child("index")) {
						ref = n["index"];
						if (ref.is_keyval()) ref >> i;
					}
					if (i > 10) break;
					if (n.has_child("depth")) {
						ref = n["depth"];
						if (ref.is_keyval()) {
							if (ref.val().begins_with("front"))
								this->sprites[i-1].layer = 2;
							if (ref.val().begins_with("middle"))
								this->sprites[i-1].layer = 0;
							if (ref.val().begins_with("behind")) 
								this->sprites[i-1].layer = 1;
						}
					}
					if (n.has_child("kills")) {
						ref = n["kills"];
						if (ref.is_seq()) {
							for(ryml::ConstNodeRef m : ref.children()) {
								CheckNodeIsVal(m);
								if (m.val().begins_with("red")) this->sprites[i-1].malevolence |= 0x1;
								if (m.val().begins_with("yellow")) this->sprites[i-1].malevolence |= 0x2;
								if (m.val().begins_with("green")) this->sprites[i-1].malevolence |= 0x4;
								if (m.val().begins_with("blue")) this->sprites[i-1].malevolence |= 0x8;
							}
						}
					}
					if (n.has_child("mask")) {
						ref = n["mask"];
						if (ref.is_keyval() && ref.val().begins_with("true")) this->sprites[i-1].mask = 1;
					}
					if (n.has_child("cleanUp")) {
						ref = n["cleanUp"];
						if (ref.is_keyval() && ref.val().begins_with("true")) this->sprites[i-1].cleanUp = 1;
					}
					if (n.has_child("strength")) {
						ref = n["strength"];
						if (ref.is_keyval()) ref >> this->sprites[i-1].strength;
					}
					if (n.has_child("blast")) {
						ref = n["blast"];
						if (ref.is_keyval()) ref >> this->sprites[i-1].blastArea;
					}
					if (n.has_child("active")) {
						ref = n["active"];
						if (ref.is_keyval() && ref.val().begins_with("true")) this->sprites[i-1].active = 1;
					}
					if (n.has_child("entryRegion")) {
						ref = n["entryRegion"];
						if (ref.has_child("left")) {
							ryml::ConstNodeRef m = ref["left"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryEntryRegion.left;
						}
						if (ref.has_child("top")) {
							ryml::ConstNodeRef m = ref["top"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryEntryRegion.top;
						}
						if (ref.has_child("right")) {
							ryml::ConstNodeRef m = ref["right"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryEntryRegion.right;
						}
						if (ref.has_child("bottom")) {
							ryml::ConstNodeRef m = ref["bottom"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryEntryRegion.bottom;
						}
					}
					if (n.has_child("exitRegion")) {
						ref = n["exitRegion"];
						if (ref.has_child("left")) {
							ryml::ConstNodeRef m = ref["left"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryExitRegion.left;
						}
						if (ref.has_child("top")) {
							ryml::ConstNodeRef m = ref["top"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryExitRegion.top;
						}
						if (ref.has_child("right")) {
							ryml::ConstNodeRef m = ref["right"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryExitRegion.right;
						}
						if (ref.has_child("bottom")) {
							ryml::ConstNodeRef m = ref["bottom"];
							if (m.is_keyval()) m >> this->sprites[i-1].furryExitRegion.bottom;
						}
					}
					if (n.has_child("fireRate")) {
						ref = n["fireRate"];
						if (ref.is_keyval()) ref >> this->sprites[i-1].fireRate;
					}
					if (n.has_child("fireStyle")) {
						ref = n["fireStyle"];
						if (ref.is_keyval()) {
							if (ref.val().begins_with("none")) this->sprites[i-1].fireType = 0;
							if (ref.val().begins_with("slow")) this->sprites[i-1].fireType = 1;
							if (ref.val().begins_with("right")) this->sprites[i-1].fireType = 2;
							if (ref.val().begins_with("left")) this->sprites[i-1].fireType = 3;
							if (ref.val().begins_with("medium")) this->sprites[i-1].fireType = 4;
							if (ref.val().begins_with("fast")) this->sprites[i-1].fireType = 5;
						}
					}
					if (n.has_child("states")) {
						ref = n["states"];
						CheckNodeIsSeq(ref);
						uint8_t j = 0;
						for(ryml::ConstNodeRef m : ref.children()) {
							j++;
							if (m.has_child("index")) {
								ref = m["index"];
								if (ref.is_keyval()) ref >> j;
							}
							if (j > 10) break;
							if (m.has_child("left")) {
								ref = m["left"];
								if (ref.is_keyval()) ref >> this->sprites[i-1].states[j-1].left;
							}
							if (m.has_child("top")) {
								ref = m["top"];
								if (ref.is_keyval()) ref >> this->sprites[i-1].states[j-1].top;
							}
							if (m.has_child("movementTarget")) {
								ref = m["movementTarget"];
								if (ref.is_keyval()) {
									ref >> this->sprites[i-1].states[j-1].destState;
									this->sprites[i-1].states[j-1].destState--;
								}
							}
							if (m.has_child("movementSpeed")) {
								ref = m["movementSpeed"];
								if (ref.is_keyval()) ref >> this->sprites[i-1].states[j-1].speed;
							}
							if (m.has_child("movementStyle")) {
								ref = m["movementStyle"];
								if (ref.is_keyval()) {
									if (ref.val().begins_with("h/v")) this->sprites[i-1].states[j-1].movementType = 0;
									if (ref.val().begins_with("diagonal")) this->sprites[i-1].states[j-1].movementType = 1;
									if (ref.val().begins_with("vertical")) this->sprites[i-1].states[j-1].movementType = 2;
									if (ref.val().begins_with("horizontal")) this->sprites[i-1].states[j-1].movementType = 3;
									if (ref.val().begins_with("track")) this->sprites[i-1].states[j-1].movementType = 4;
									if (ref.val().begins_with("fast")) this->sprites[i-1].states[j-1].movementType = 5;
									if (ref.val().begins_with("none")) this->sprites[i-1].states[j-1].movementType = 6;
								}
							}
							if (m.has_child("gravity")) {
								ref = m["gravity"];
								if (ref.is_keyval() && ref.val().begins_with("true")) this->sprites[i-1].states[j-1].gravity = 1;
							}
							if (m.has_child("current")) {
								ref = m["current"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].current;
										this->sprites[i-1].states[j-1].current--;
									}
								}
								if (ref.has_child("change")) {
									ryml::ConstNodeRef k = ref["change"];
									if (k.is_keyval()) {
										if (k.val().begins_with("on")) this->sprites[i-1].states[j-1].current |= 0x20;
										if (k.val().begins_with("off")) this->sprites[i-1].states[j-1].current |= 0x10;
									}
								}
							}
							if (m.has_child("otherSprite")) {
								ref = m["otherSprite"];
								if (ref.is_keyval()) {
									ref >> this->sprites[i-1].states[j-1].activateSprite;
									this->sprites[i-1].states[j-1].activateSprite--;
								}
							}
							if (m.has_child("furryEntryRegion")) {
								ref = m["furryEntryRegion"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].entryTrigger.state;
										this->sprites[i-1].states[j-1].entryTrigger.state--;
									}
								}
								if (ref.has_child("left")) {
									ryml::ConstNodeRef k = ref["left"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].entryTrigger.left;
								}
								if (ref.has_child("top")) {
									ryml::ConstNodeRef k = ref["top"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].entryTrigger.top;
								}
								if (ref.has_child("right")) {
									ryml::ConstNodeRef k = ref["right"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].entryTrigger.right;
								}
								if (ref.has_child("bottom")) {
									ryml::ConstNodeRef k = ref["bottom"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].entryTrigger.bottom;
								}
							}
							if (m.has_child("furryExitRegion")) {
								ref = m["furryExitRegion"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].exitTrigger.state;
										this->sprites[i-1].states[j-1].exitTrigger.state--;
									}
								}
								if (ref.has_child("left")) {
									ryml::ConstNodeRef k = ref["left"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].exitTrigger.left;
								}
								if (ref.has_child("top")) {
									ryml::ConstNodeRef k = ref["top"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].exitTrigger.top;
								}
								if (ref.has_child("right")) {
									ryml::ConstNodeRef k = ref["right"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].exitTrigger.right;
								}
								if (ref.has_child("bottom")) {
									ryml::ConstNodeRef k = ref["bottom"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].exitTrigger.bottom;
								}
							}
							if (m.has_child("spriteEntryRegion")) {
								ref = m["spriteEntryRegion"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].spriteEntryTrigger.state;
										this->sprites[i-1].states[j-1].spriteEntryTrigger.state--;
									}
								}
								if (ref.has_child("left")) {
									ryml::ConstNodeRef k = ref["left"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteEntryTrigger.left;
								}
								if (ref.has_child("top")) {
									ryml::ConstNodeRef k = ref["top"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteEntryTrigger.top;
								}
								if (ref.has_child("right")) {
									ryml::ConstNodeRef k = ref["right"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteEntryTrigger.right;
								}
								if (ref.has_child("bottom")) {
									ryml::ConstNodeRef k = ref["bottom"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteEntryTrigger.bottom;
								}
							}
							if (m.has_child("spriteExitRegion")) {
								ref = m["spriteExitRegion"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].spriteExitTrigger.state;
										this->sprites[i-1].states[j-1].spriteExitTrigger.state--;
									}
								}
								if (ref.has_child("left")) {
									ryml::ConstNodeRef k = ref["left"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteExitTrigger.left;
								}
								if (ref.has_child("top")) {
									ryml::ConstNodeRef k = ref["top"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteExitTrigger.top;
								}
								if (ref.has_child("right")) {
									ryml::ConstNodeRef k = ref["right"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteExitTrigger.right;
								}
								if (ref.has_child("bottom")) {
									ryml::ConstNodeRef k = ref["bottom"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].spriteExitTrigger.bottom;
								}
							}
							if (m.has_child("destroy")) {
								ref = m["destroy"];
								if (ref.is_keyval() && ref.val().begins_with("true")) this->sprites[i-1].states[j-1].destroy = 1;
							}
							if (m.has_child("bounce")) {
								ref = m["bounce"];
								if (ref.is_keyval() && ref.val().begins_with("true")) this->sprites[i-1].states[j-1].bounce = 1;
							}
							if (m.has_child("empty")) {
								ref = m["empty"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].emptyWater.region;
										this->sprites[i-1].states[j-1].emptyWater.region--;
									}
								}
								if (ref.has_child("speed")) {
									ryml::ConstNodeRef k = ref["speed"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].emptyWater.speed;
									}
								}
							}
							if (m.has_child("fill")) {
								ref = m["fill"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].fillWater.region;
										this->sprites[i-1].states[j-1].fillWater.region--;
									}
								}
								if (ref.has_child("speed")) {
									ryml::ConstNodeRef k = ref["speed"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].fillWater.speed;
									}
								}
							}
							if (m.has_child("waterChangeRegion")) {
								ref = m["waterChangeRegion"];
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].destWaterState;
										this->sprites[i-1].states[j-1].destWaterState--;
									}
								}
								if (ref.has_child("left")) {
									ryml::ConstNodeRef k = ref["left"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].waterTriggerLeft;
								}
								if (ref.has_child("top")) {
									ryml::ConstNodeRef k = ref["top"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].waterTriggerTop;
								}
								if (ref.has_child("right")) {
									ryml::ConstNodeRef k = ref["right"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].waterTriggerRight;
								}
								if (ref.has_child("bottom")) {
									ryml::ConstNodeRef k = ref["bottom"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].waterTriggerBottom;
								}
							}
							if (m.has_child("animation")) {
								ref = m["animation"];
								if (ref.has_child("speed")) {
									ryml::ConstNodeRef k = ref["speed"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].animationSpeed;
								}
								if (ref.has_child("repeat")) {
									ryml::ConstNodeRef k = ref["repeat"];
									if (k.is_keyval() && k.val().begins_with("true")) this->sprites[i-1].states[j-1].cycle = 1;
								}
								if (ref.has_child("count")) {
									ryml::ConstNodeRef k = ref["count"];
									if (k.is_keyval()) k >> this->sprites[i-1].states[j-1].cycleCount;
								}
								if (ref.has_child("index")) {
									ryml::ConstNodeRef k = ref["index"];
									if (k.is_keyval()) {
										k >> this->sprites[i-1].states[j-1].animationTriggerState;
										this->sprites[i-1].states[j-1].animationTriggerState--;
									}
								}
								if (ref.has_child("frames")) {
									ref = ref["frames"];
									CheckNodeIsSeq(ref);
									uint8_t k = 0;
									for(ryml::ConstNodeRef l : ref.children()) {
										k++;
										if (k > 10) break;
										if (l.has_child("left")) {
											ryml::ConstNodeRef o = l["left"];
											if (o.is_keyval()) o >> this->sprites[i-1].states[j-1].frames[k-1].left;
										}
										if (l.has_child("top")) {
											ryml::ConstNodeRef o = l["top"];
											if (o.is_keyval()) o >> this->sprites[i-1].states[j-1].frames[k-1].top;
										}
										if (l.has_child("right")) {
											ryml::ConstNodeRef o = l["right"];
											if (o.is_keyval()) o >> this->sprites[i-1].states[j-1].frames[k-1].right;
										}
										if (l.has_child("bottom")) {
											ryml::ConstNodeRef o = l["bottom"];
											if (o.is_keyval()) o >> this->sprites[i-1].states[j-1].frames[k-1].bottom;
										}
									}
								}
							}
						}
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
					ConvertYaml(buffer, this, GetComment());
					break;
				default: 
					Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_BIN_UNRECOGNISED_FORMAT);
			}
		}
		void Bin::SetComment(std::string comment) {
			int16_t len = (int16_t)comment.length() + 1;
			if (len > 3000) {
				Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_BIN_COMMENT_OVERFLOW);
			}
			const char *str = comment.c_str();
			for (uint8_t y = 50; y > 12; y--) {
				uint8_t x = (1024 / (y + 1));
				for (; x < 78; x++) {
					this->map[y][x].x = *str++;
					this->map[y][x].y = *str++;
					len -= 2;
					if (len < 1) return;
				}
			}
		}
		std::string Bin::GetComment() {
			std::string str;
			for (uint8_t y = 50; y > 12; y--) {
				uint8_t x = (1024 / (y + 1));
				for (; x < 78; x++) {
					char c = (char)this->map[y][x].x;
					if (!c) return str;
					str += c;
					c = (char)this->map[y][x].y;
					if (!c) return str;
					str+= c;
				}
			}
			return str;
		}
	}
}