using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace mmm_debugger
{
    /// <summary>
    /// Interaction logic for SessionManagerView.xaml
    /// </summary>
    public partial class SessionManagerView : UserControl
    {
        public SessionManagerView()
        {
            InitializeComponent();
            var sessionManager = new ViewModel.SessionManagerViewModel(new Model.SessionManager());

            sessionManager.OnSessionAdded += new EventHandler(sessionManager_OnSessionAdded);

            this.DataContext = sessionManager;
        }

        void sessionManager_OnSessionAdded(object sender, EventArgs e)
        {
            Application.Current.Dispatcher.Invoke((Action)delegate { sessionsTabs.SelectedIndex = sessionsTabs.Items.Count - 1; });
        }

        /// <summary>
        /// Closes the session that is referenced by this button.
        /// </summary>
        /// <param name="sender">The sending object</param>
        /// <param name="e">Some args or something, who knows.</param>
        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)e.Source;
            ViewModel.SessionViewModel session = (ViewModel.SessionViewModel)button.DataContext;

            session.Disconnect();
            (this.DataContext as ViewModel.SessionManagerViewModel).Terminate(session);
        }

        private void Save_Clicked(object sender, RoutedEventArgs e)
        {
            var currentSession = sessionsTabs.SelectedContent as ViewModel.SessionViewModel;
            if (currentSession == null)
            {
                return;
            }

            //Prompt the user to save the log somewhere.
            Microsoft.Win32.SaveFileDialog dialog = new Microsoft.Win32.SaveFileDialog();
            dialog.DefaultExt = ".txt";
            dialog.Filter = "Text Files (.txt)|*.txt";
            if (dialog.ShowDialog() == true)
            {
                currentSession.Save(dialog.FileName);
            }
        }
    }
}
