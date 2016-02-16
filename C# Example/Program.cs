/*
Include NGCP_COM.dll

Protosharp is a sample C# program using a Protonet session.
The periodic node entry messages and two sample messages
are displayed in the console.
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Protonet;

namespace protosharp
{
    /*Hold all state and behavior data in this callback class*/
    public class ProtonetCallbacks
    {
        public ProtonetCallbacks()
        {
        }
        public void OnPing(
            sbyte link_id,
            ref Protonet.Header header,
            ref Protonet.Ping rx_msg,
            Protonet.Node node)
        {
            Console.WriteLine("Output stuff");
        }
        public void OnPong(
            sbyte link_id,
            ref Protonet.Header header,
            ref Protonet.Pong rx_msg,
            Protonet.Node node)
        {
            
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            /*Create a protonet node at specified node id (2)*/
            Protonet.Node UgvNode = new Protonet.Node(2);

            /*Construct class to hold all callbacks and behaviors*/
            ProtonetCallbacks UgvCallbacks = new ProtonetCallbacks();

            /*Create a link id variable to reference a created datalink*/
            sbyte link_id = 0;

            /*
            Register the methods of the callback class with Protonet
            Note that this is not a HARDWARE register. It passes the callback
            so the handler can execute it when the respective message is received
            */
            UgvNode.RegisterPingEvent(UgvCallbacks.OnPing);
            UgvNode.RegisterPongEvent(UgvCallbacks.OnPong);


            /*Add a new datalink to the Protonet session and establish an endpoint*/
            UgvNode.AddUDPDatalink(out link_id, 1337);
            UgvNode.EstablishUDPEndpoint(link_id, 2,1337, "127.0.0.1");
            

            /*Loop forever*/
            while (true)
            {
                System.Threading.Thread.Sleep(1000);
                UgvNode.SendPing(2, 0);

            }
        }
    }
}


