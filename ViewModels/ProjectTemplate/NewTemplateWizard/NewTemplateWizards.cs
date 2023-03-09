using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    public static class NewTemplateWizards
    {
        private static List<KeyValuePair<List<string>, Type>> _wizards = new List<KeyValuePair<List<string>, Type>>();


        public static List<KeyValuePair<List<string>, Type>> Wizards 
        { 
            get 
            { 
                if (_wizards.Count == 0) 
                {
                    var types = Assembly.GetExecutingAssembly()
                                    .GetTypes();
                    foreach(Type t in types)
                    {
                        var attributes = t.GetCustomAttributes(typeof(NewTemplateWizardAttribute))
                            .Cast<NewTemplateWizardAttribute>()
                            .Select(a => a.Statement)
                            .ToList();
                        if (attributes.Count() > 0)
                        {
                            _wizards.Add(new KeyValuePair<List<string>, Type>(attributes, t));
                        }
                    }
                }
                return _wizards; 
            } 
        }
    }
}
