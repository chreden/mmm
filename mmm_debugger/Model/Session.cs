using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections.ObjectModel;

using System.Windows;
using System.ComponentModel;

namespace mmm_debugger.Model
{
    /// <summary>
    /// A session represents a past, current or pending connection to a 
    /// MMM debug mission.
    /// </summary>
    public class Session
    {
        private delegate void SetDisconnectedDelegate(String message);
        private delegate void AddMessageDelegate(Message m);

        private TcpClient       connection;
        private ConnectionState connectionState;
        
        public event EventHandler ConnectionStateChanged;

        public class MessageArgs
            : EventArgs
        {
            public Message Message
            {
                get;
                private set;
            }

            public MessageArgs(Message message)
            {
                Message = message;
            }
        }

        /// <summary>
        /// Describes the current status of the connection between the Session and the server
        /// inside MMM.
        /// </summary>
        public enum ConnectionState
        {
            /// <summary>
            /// The Session has in the process of connecting to the MMM session.
            /// </summary>
            Connecting,
            /// <summary>
            /// The Session has connected to the MMM sever and is ready to exchange messages.
            /// </summary>
            Connected,
            /// <summary>
            /// The Session has been disconnected from the MMM server.
            /// </summary>
            Disconnected
        };

        /// <summary>
        /// Current status of the connection with the MMM debugger.
        /// </summary>
        public ConnectionState CurrentConnectionState
        {
            get
            {
                return connectionState;
            }
            private set
            {
                this.connectionState = value;
                if (ConnectionStateChanged != null)
                {
                    ConnectionStateChanged.Invoke(this, null);
                }
            }
        }

        /// <summary>
        /// Name used to refer to this connection. Of no consequence to
        /// the operation of the session.
        /// </summary>
        public String Name
        {
            get;
            set;
        }

        /// <summary>
        /// Forcibly disconnect from the mission we are connected to.
        /// </summary>
        public void Disconnect()
        {
            this.connection.Close();
            this.CurrentConnectionState = ConnectionState.Disconnected;
        }
        
        /// <summary>
        /// Event for when a message is received from the MMM mission.
        /// </summary>
        public event EventHandler<MessageArgs> MessageReceived;

        public Session( TcpClient connection )
        {
            this.Name                   = DateTime.Now.ToString();
            this.CurrentConnectionState = ConnectionState.Connected;
            this.connection             = connection;

            this.Messages         = new ObservableCollection<Message>();
            this.MessageReceived += new EventHandler<MessageArgs>(Session_MessageReceived);

            //Set up the first step for receiving a message. Everything else gets
            //chained on.
            StartMessageRead();
        }

        /// <summary>
        /// Used to create a message that may span multiple network buffer reads.
        /// When it is completed a real message is constructed from the data accumulated.
        /// </summary>
        private class MessageUnderConstruction
        {
            /// <summary>
            /// The raw data being used for the current stage of message construction.
            /// </summary>
            public byte[] Buffer
            {
                get;
                set;
            }

            /// <summary>
            /// The type of the message that is under construction.
            /// </summary>
            public Message.MessageType Type
            {
                get;
                set;
            }

            /// <summary>
            /// The length of the text string 
            /// </summary>
            public int TextLength
            {
                get;
                set;
            }

            /// <summary>
            /// The text to be displayed for the message under construction.
            /// </summary>
            public String Text
            {
                get;
                set;
            }
        }

        private void StartMessageRead()
        {
            try
            {
                NetworkStream stream             = this.connection.GetStream();
                //Start a new message - this might stretch over multiple buffers until a 
                //real message can be constructed out of it.
                MessageUnderConstruction message = new MessageUnderConstruction();
                message.Buffer = new Byte[sizeof(int)];
                stream.BeginRead(message.Buffer, 0, message.Buffer.Length, OnMessageTypeRead, message);
            }
            catch (Exception e)
            {
                Application.Current.Dispatcher.Invoke(new SetDisconnectedDelegate(SetDisconnected), e.ToString());
            }
        }

        /// <summary>
        /// React to a disconnection from the MMM server. This informs the user of the change
        /// in state as well as updating the state.
        /// </summary>
        private void SetDisconnected(String message)
        {
            this.CurrentConnectionState = ConnectionState.Disconnected;
            this.MessageReceived.Invoke(this, new MessageArgs(new Message("Disconnected : " + message, Message.MessageType.Error)));
        }

        /// <summary>
        /// Second stage of message accumulation - this finishes the read of the type of the new
        /// message.
        /// </summary>
        /// <param name="result">IAsyncResult associated with this read callback</param>
        private void OnMessageTypeRead(IAsyncResult result)
        {
            if (!this.connection.Connected)
            {
                return;
            }

            try
            {
                NetworkStream stream = this.connection.GetStream();
                if (sizeof(int) != stream.EndRead(result))
                {
                    throw new Exception("Failed to read message type");
                }
                MessageUnderConstruction message = (MessageUnderConstruction)result.AsyncState;
                message.Type = (Message.MessageType)BitConverter.ToInt32(message.Buffer, 0);
                //We can re-use the buffer without reallocating it since the size is the same.
                stream.BeginRead(message.Buffer, 0, sizeof(int), OnMessageLengthRead, message);
            }
            catch( Exception e )
            {
                Application.Current.Dispatcher.Invoke(new SetDisconnectedDelegate(SetDisconnected), e.ToString());
            }
        }

        /// <summary>
        /// Second stage of message accumulation - this finishes the read of the length of the text
        /// of the new message.
        /// </summary>
        /// <param name="result">IAsyncResult associated with this read callback</param>
        private void OnMessageLengthRead(IAsyncResult result)
        {
            if (!this.connection.Connected)
            {
                return;
            }

            try
            {
                NetworkStream stream = this.connection.GetStream();
                if (sizeof(int) != stream.EndRead(result))
                {
                    throw new Exception("Failed to read message length");
                }

                MessageUnderConstruction message = (MessageUnderConstruction)result.AsyncState;
                message.TextLength = BitConverter.ToInt32(message.Buffer, 0);
                message.Buffer = new Byte[message.TextLength];
                stream.BeginRead(message.Buffer, 0, message.TextLength, OnMessageTextRead, message);
            }
            catch (Exception e)
            {
                Application.Current.Dispatcher.Invoke(new SetDisconnectedDelegate(SetDisconnected), e.ToString());
            }
        }

        private void OnMessageTextRead(IAsyncResult result)
        {
            if (!this.connection.Connected)
            {
                return;
            }

            try
            {
                MessageUnderConstruction message = (MessageUnderConstruction)result.AsyncState;
                NetworkStream stream = this.connection.GetStream();
                if (message.TextLength != stream.EndRead(result))
                {
                    throw new Exception("Failed to read message text");
                }
             
                message.Text = Encoding.ASCII.GetString(message.Buffer);
                if (this.MessageReceived != null)
                {
                    this.MessageReceived.Invoke(this, new MessageArgs(new Message(message.Text, message.Type)));
                }
                StartMessageRead();
            }
            catch (Exception e )
            {
                Application.Current.Dispatcher.Invoke(new SetDisconnectedDelegate(SetDisconnected), e.ToString());
            }
        }

        /// <summary>
        /// All messages that have been received by this session so far.
        /// </summary>
        public Collection<Message> Messages
        {
            get;
            private set;
        }

        private void AddMessage(Message m)
        {
            this.Messages.Add(m);
        }

        private void Session_MessageReceived(object sender, Session.MessageArgs e)
        {
            if (Application.Current == null)
            {
                return;
            }
            Application.Current.Dispatcher.Invoke(new AddMessageDelegate(AddMessage), e.Message);
        }

        private void EndSend(IAsyncResult ar)
        {
            this.connection.GetStream().EndWrite(ar);
        }

        /// <summary>
        /// Send a command to be executed in the MMM game
        /// </summary>
        /// <param name="command">The lua script to be executed</param>
        public void SendCommand(String command)
        {
            if (command == null)
            {
                throw new ArgumentNullException("Script command cannot be null");
            }

            try
            {
                NetworkStream stream = this.connection.GetStream();
                List<byte>    data   = new List<byte>();
                data.AddRange(BitConverter.GetBytes(command.Length));
                data.AddRange(Encoding.ASCII.GetBytes(command));
                stream.BeginWrite(data.ToArray(), 0, data.Count, EndSend, null);
            }
            catch (Exception e)
            {
                Application.Current.Dispatcher.Invoke(new SetDisconnectedDelegate(SetDisconnected), e.ToString());
            }
        }
    }
}
