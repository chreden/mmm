using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows;
using System.Collections.ObjectModel;

namespace mmm_debugger.Model
{
    /// <summary>
    /// Listens for connections and makes new sessions when it gets a new
    /// conection.
    /// </summary>
    class SessionManager
    {
        private const int DefaultPort = 6000;
        private TcpListener listener;

        public class SessionArgs
            : EventArgs
        {
            public Session Session
            {
                get;
                private set;
            }

            public SessionArgs(Session session)
            {
                this.Session = session;
            }
        }

        public event EventHandler<SessionArgs> SessionStarted;

        public Collection<Session> Sessions
        {
            get;
            private set;
        }

        private void AcceptClient(IAsyncResult ar)
        {
            TcpClient client        = this.listener.EndAcceptTcpClient(ar);
            Session newSession      = new Session(client);
            SessionStarted.Invoke(this, new SessionArgs(newSession));
            this.listener.BeginAcceptTcpClient(new AsyncCallback(AcceptClient), this.listener);
        }

        void SessionManager_SessionStarted(object sender, SessionManager.SessionArgs e)
        {
            if (Application.Current == null)
            {
                return;
            }
            this.Sessions.Add(e.Session);
        }

        public SessionManager()
        {
            this.Sessions = new Collection<Session>();
            this.SessionStarted += new EventHandler<SessionArgs>(SessionManager_SessionStarted);
            this.listener = new TcpListener(IPAddress.Any, DefaultPort);
            this.listener.Start();
            this.listener.BeginAcceptTcpClient(new AsyncCallback(AcceptClient), this.listener);
        }
    }
}
