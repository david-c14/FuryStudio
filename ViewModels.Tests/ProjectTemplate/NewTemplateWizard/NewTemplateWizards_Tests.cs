using carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard;

namespace carbon14.FuryStudio.ViewModels.Tests.ProjectTemplate.NewTemplateWizard
{
    public class NewTemplateWizards_Tests
    {
        [Fact]
        public void When_I_call_for_a_list_of_wizards_Then_I_get_a_dictionary_of_knowledge_paths_and_wizards()
        {
            //Arrange

            //Act
            List<KeyValuePair<List<string>, Type>> dict = NewTemplateWizards.Wizards;

            //Assert
            Assert.Equal(4, dict.Count);
            KeyValuePair<List<string>, Type> entry = dict.Where(e => e.Value == typeof(NewTemplate_Fury_AmigaVM)).FirstOrDefault();
            Assert.Equal(2, entry.Key.Count);
            entry = dict.Where(e => e.Value == typeof(NewTemplate_Fury_Dos_InstalledDirectoryVM)).FirstOrDefault();
            Assert.Equal(3, entry.Key.Count);
            entry = dict.Where(e => e.Value == typeof(NewTemplate_Fury_Dos_SingleZipVM)).FirstOrDefault();
            Assert.Equal(3, entry.Key.Count);
            entry = dict.Where(e => e.Value == typeof(NewTemplate_Pac_AmigaVM)).FirstOrDefault();
            Assert.Equal(2, entry.Key.Count);
        }
    }
}
