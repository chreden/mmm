using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;

namespace mmm_debugger.ViewModel
{
    class SessionViewModel : INotifyPropertyChanged
    {
        private Model.Session session;
        public event PropertyChangedEventHandler PropertyChanged;

        public SessionViewModel(Model.Session session)
        {
            this.session = session;
            this.session.MessageReceived += new EventHandler<Model.Session.MessageArgs>(session_MessageReceived);
            this.session.ConnectionStateChanged += new EventHandler(session_ConnectionStateChanged);
        }

        private void OnPropertyChanged(String name)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        private void session_ConnectionStateChanged(object sender, EventArgs e)
        {
            OnPropertyChanged("CurrentConnectionState");
        }

        private void session_MessageReceived(object sender, Model.Session.MessageArgs e)
        {
            OnPropertyChanged("Messages");
        }

        /// <summary>
        /// Disconnect the session from the MMM server.
        /// </summary>
        public void Disconnect()
        {
            this.session.Disconnect();
        }

        /// <summary>
        /// Current state of the connection between the session and the MMM server.
        /// </summary>
        public Model.Session.ConnectionState CurrentConnectionState
        {
            get
            {
                return session.CurrentConnectionState;
            }
        }

        /// <summary>
        /// Current name of the session
        /// </summary>
        public String Name
        {
            get
            {
                return this.session.Name;
            }
        }

        internal Model.Session InnerSession
        {
            get
            {
                return session;
            }
        }

        /// <summary>
        /// All messages that have been received by this session so far.
        /// </summary>
        public ObservableCollection<MessageViewModel> Messages
        {
            get
            {
                return new ObservableCollection<MessageViewModel>(from m in session.Messages select new MessageViewModel(m));
            }
        }

        /// <summary>
        /// Send a command to be executed on the MMM server.
        /// </summary>
        /// <param name="command">The Lua script to be executed.</param>
        public void SendCommand(String command)
        {
            this.session.SendCommand(command);
        }

        /// <summary>
        /// Save all of the messages currently received in this session to file.
        /// </summary>
        /// <param name="filename"></param>
        public void Save(String filename)
        {
            StringBuilder builder = new StringBuilder();
            foreach (var message in this.session.Messages)
            {
                builder.AppendLine(message.ToString());
            }

            try
            {
                System.IO.File.WriteAllText(filename, builder.ToString());
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error saving file : " + ex.ToString());
            }
        }
    }
}
