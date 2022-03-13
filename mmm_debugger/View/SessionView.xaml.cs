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
    /// Interaction logic for SessionView.xaml
    /// </summary>
    public partial class SessionView : UserControl
    {
        public SessionView()
        {
            InitializeComponent();
        }

        delegate void ScrollTheStupidMessageDelegate(Model.Message message);

        void ScrollTheStupidMessage(Model.Message message)
        {
            messageList.ScrollIntoView(message);
        }

        void SessionView_MessageReceived(object sender, Model.Session.MessageArgs e)
        {
            Application.Current.Dispatcher.Invoke(new ScrollTheStupidMessageDelegate(ScrollTheStupidMessage), e.Message);
        }

        private void sendButton_Click(object sender, RoutedEventArgs e)
        {
            var session = this.DataContext as ViewModel.SessionViewModel;
            session.SendCommand(new TextRange(commandBox.Document.ContentStart,
                                              commandBox.Document.ContentEnd).Text);
        }
    }
}
