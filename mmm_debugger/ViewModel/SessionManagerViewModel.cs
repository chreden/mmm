using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace mmm_debugger.ViewModel
{
    class SessionManagerViewModel : INotifyPropertyChanged
    {
        delegate void SessionAdded();

        private Model.SessionManager sessionManager;
        public event PropertyChangedEventHandler PropertyChanged;
        public event EventHandler OnSessionAdded;

        public SessionManagerViewModel(Model.SessionManager manager)
        {
            this.sessionManager = manager;
            this.sessionManager.SessionStarted += new EventHandler<Model.SessionManager.SessionArgs>(sessionManager_SessionStarted);
        }

        private void OnPropertyChanged(String name)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        /// <summary>
        /// Remove the session from the session manager.
        /// </summary>
        /// <param name="session">The session to remove</param>
        public void Terminate(SessionViewModel session)
        {
            sessionManager.Sessions.Remove(sessionManager.Sessions.FirstOrDefault(s => s == session.InnerSession));
            OnPropertyChanged("Sessions");
        }

        void sessionManager_SessionStarted(object sender, Model.SessionManager.SessionArgs e)
        {
            OnPropertyChanged("Sessions");
            OnSessionAdded.Invoke(this, null);
        }

        /// <summary>
        /// All current sessions - this may include both disconected and connected
        /// sessions.
        /// </summary>
        public ObservableCollection<SessionViewModel> Sessions
        {
            get
            {
                return new ObservableCollection<SessionViewModel>(from s in sessionManager.Sessions 
                                                                  select new SessionViewModel(s));
            }
        }
    }
}
