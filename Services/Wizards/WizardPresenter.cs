using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Wizards
{
    public class WizardPresenter : IWizardPresenter
    {
        private List<IWizardPagePresenter> _pages = new List<IWizardPagePresenter>();
        private IWizardPagePresenter _currentPage = null;

        public WizardPresenter(IWizardView view)
        {
            View = view;
            view.Next += View_Next;
            view.Prev += View_Prev;
        }

        private void View_Prev(object sender, EventArgs e)
        {
            IWizardPagePresenter page = GetPrevPage();
            if (page == null)
            {
                return;
            }
            if (!PageChanging(page))
            {
                return;
            }
            _currentPage = page;
            View.SetView(_currentPage.View);
            PageChanged(page);
            UpdatePage();
        }

        private void View_Next(object sender, EventArgs e)
        {
            IWizardPagePresenter page = GetNextPage();
            if (!PageChanging(page))
            {
                return;
            }
            _currentPage = page;
            if (_currentPage == null)
            {
                View.CloseDialog(System.Windows.Forms.DialogResult.OK);
                return;
            }
            View.SetView(_currentPage.View);
            PageChanged(page);
            UpdatePage();
        }

        protected void UpdatePage()
        {
            if (_currentPage == null)
            {
                return;
            }
            View.NextEnabled = NextEnabled();
            View.PrevEnabled = PrevEnabled();
            View.NextCaption = NextCaption();
        }

        public IWizardView View { get; }

        public int PageCount => _pages.Count;

        public void AddPage(IWizardPagePresenter page)
        {
            _pages.Add(page);
            View.AddView(page.View);
            if (_currentPage == null)
            {
                _currentPage = page;
                View.SetView(page.View);
            }
            UpdatePage();
        }

        public void RemovePage(IWizardPagePresenter page)
        {
            int index = IndexOf(page);
            _pages.Remove(page);
            View.RemoveView(page.View);
            if (_currentPage == page)
            {
                _currentPage = null;
                View.SetView(null);
                while (index >= PageCount)
                    index--;
                if (index > -1)
                {
                    _currentPage = _pages[index];
                    View.SetView(_currentPage.View);
                }
            }
            UpdatePage();
        }

        public void RemovePage(int index)
        {
            RemovePage(_pages[index]);
        }

        public int IndexOf(IWizardPagePresenter page)
        {
            return _pages.IndexOf(page);
        }

        public IWizardPagePresenter CurrentPage => _currentPage;

        protected virtual IWizardPagePresenter GetNextPage()
        {
            if (_currentPage == null)
                return null;
            int currentIndex = IndexOf(_currentPage);
            if (currentIndex == -1)
                return null;
            if (currentIndex > PageCount - 2)
                return null;
            return _pages[currentIndex + 1];
        }

        protected virtual IWizardPagePresenter GetPrevPage()
        {
            if (_currentPage == null)
                return null;
            int currentIndex = IndexOf(_currentPage);
            if (currentIndex < 1)
                return null;
            return _pages[currentIndex - 1];
        }

        public IWizardPagePresenter NextPage => GetNextPage();

        public IWizardPagePresenter PrevPage => GetPrevPage();

        protected virtual bool PageChanging(IWizardPagePresenter page)
        {
            return true;
        }

        protected virtual void PageChanged(IWizardPagePresenter page)
        {
            return;
        }

        protected virtual bool NextEnabled()
        {
            return true;
        }

        protected virtual bool PrevEnabled()
        {
            return (PrevPage != null);
        }

        protected virtual string NextCaption()
        {
            string caption = "&Next";
            if (_currentPage == null)
            {
                return caption;
            }
            int index = IndexOf(_currentPage);
            if (index >= PageCount - 1)
            {
                caption = "&Finish";
            }
            return caption;
        }

    }
}
