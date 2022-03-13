using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media;

namespace mmm_debugger.ViewModel
{
    class MessageViewModel
    {
        private Model.Message message;

        public MessageViewModel(Model.Message message)
        {
            this.message = message;
        }

        /// <summary>
        /// The colour that should be used to render the text in the 
        /// message display. This will be different depending on the
        /// type of message.
        /// </summary>
        public Brush Color
        {
            get
            {
                switch (this.message.Type)
                {
                    case Model.Message.MessageType.Error:
                        return Brushes.Red;
                }
                return Brushes.Black;
            }
        }

        public override string ToString()
        {
            return this.message.ToString();
        }
    }
}
