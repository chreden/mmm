using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media;

namespace mmm_debugger.Model
{
    /// <summary>
    /// A message to be sent through to the running MMM application, or one that
    /// has been received.
    /// </summary>
    public class Message
    {
        /// <summary>
        /// The message text as re-routed from an MMM Lua print, or an MMM lua 
        /// error message
        /// </summary>
        public String Text
        {
            get;
            private set;
        }

        /// <summary>
        /// Indicates how this message will be rendered in both MMM and the remote
        /// debugger
        /// </summary>
        public enum MessageType
        {
            /// <summary>
            /// A standard message as routed from the standard Lua print command.
            /// </summary>
            Normal,
            /// <summary>
            /// A test message
            /// </summary>
            Test,
            /// <summary>
            /// Created as a result of a script error - rerouted directly from the MMM error function.
            /// </summary>
            Error
        }

        /// <summary>
        /// Used to decide how to render the message in both MMM and in the remote debugger terminal
        /// itself.
        /// </summary>
        public MessageType Type
        {
            get;
            private set;
        }

        public override string ToString()
        {
            return this.Text;
        }

        /// <summary>
        /// Create a new message for display in the remote debugger or in the
        /// MMM console.
        /// </summary>
        /// <param name="text">The text to display in the status window</param>
        /// <param name="type">Controls how the message is handled</param>
        public Message(String text, MessageType type)
        {
            this.Text = text;
            this.Type = type;
        }
    }
}
