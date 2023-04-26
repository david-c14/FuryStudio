using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.WinUI.MVVM.ViewCollection;
using System.Collections;

namespace carbon14.FuryStudio.WinUI.MVVM.Carousel
{
    public partial class CarouselControl : ViewCollectionControl
    {
        private int _selectedIndex = -1;

        public CarouselControl()
        {
            InitializeComponent();
        }

        public int SelectedIndex
        {
            get => _selectedIndex;
            set
            {
                if (_selectedIndex != value)
                {
                    if (value < 0 || value >= Controls.Count)
                    {
                        throw new IndexOutOfRangeException(nameof(SelectedIndex));
                    }
                    SuspendLayout();
                    try
                    {
                        Controls[_selectedIndex].Visible = false;
                        _selectedIndex = value;
                        Controls[_selectedIndex].Visible = true;
                    }
                    finally
                    {
                        ResumeLayout();
                    }
                }
            }
        }

        protected override void OnAddRange(IList viewModels)
        {
            SuspendLayout();
            try
            {
                base.OnAddRange(viewModels);
            }
            finally
            {
                ResumeLayout();
            }
        }

        protected override bool OnAdd(IViewModelBase viewModel)
        {
            bool result = base.OnAdd(viewModel);
            if (result)
            {
                if (_selectedIndex == -1)
                {
                    _selectedIndex = Controls.Count - 1;
                    Controls[_selectedIndex].Visible = true;
                }
                else
                {
                    Controls[Controls.Count - 1].Visible = false;
                }
            }
            return result;
        }

        protected override void OnClear()
        {
            base.OnClear();
            _selectedIndex = -1;
        }

        protected override void OnRemove(int index)
        {
            SuspendLayout();
            try
            {
                base.OnRemove(index);
                if (index == _selectedIndex)
                {
                    if (_selectedIndex == -1)
                        return;
                    if (_selectedIndex > 0)
                    {
                        _selectedIndex--;
                        Controls[_selectedIndex].Visible = true;
                        return;
                    }
                    if (Controls.Count > 0)
                    {
                        _selectedIndex = 0;
                        Controls[_selectedIndex].Visible = true;
                        return;
                    }
                    _selectedIndex = -1;
                }
            }
            finally
            {
                ResumeLayout();
            }
        }

        protected override void OnInsertRange(int index, IList viewModels)
        {
            SuspendLayout();
            try
            {
                base.OnInsertRange(index, viewModels);
            }
            finally
            {
                ResumeLayout();
            }
        }

        protected override bool OnInsert(int index, IViewModelBase viewModel)
        {
            bool result = base.OnInsert(index, viewModel);
            if (result)
            {
                if (index == _selectedIndex)
                {
                    Controls[index].Visible = false;
                    _selectedIndex++;
                    Controls[_selectedIndex].Visible = true;
                }
                else if (index == -1 && Controls.Count == 1)
                {
                    _selectedIndex = 0;
                    Controls[0].Visible = true;
                }
            }
            return result;
        }

        protected override void OnReplaceRange(int index, int count, IList viewModels)
        {
            SuspendLayout();
            try
            {
                base.OnReplaceRange(index, count, viewModels);
            }
            finally
            {
                ResumeLayout();
            }
        }

        protected override bool OnReplace(int index, IViewModelBase viewModel)
        {
            bool result = base.OnReplace(index, viewModel);
            if (result)
            {
                Controls[index].Visible = (index == _selectedIndex);
            }
            return result;
        }
    }
}
