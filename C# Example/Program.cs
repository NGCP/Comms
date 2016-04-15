
/*
Comsharp is a sample C# program using a Comnet session.
The periodic node entry messages and two sample messages
are displayed in the console.
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Comnet;

namespace Comsharp
{
    /*Hold all state and behavior data in this callback class*/
    public class ComnetCallbacks
    {
        public ComnetCallbacks()
        {
        }
        public void OnPing(
            sbyte link_id,
            ref Comnet.Header header,
            ref Comnet.Ping rx_msg,
            Comnet.Node node)
        {
            
        }
        public void OnPong(
            sbyte link_id,
            ref Comnet.Header header,
            ref Comnet.Pong rx_msg,
            Comnet.Node node)
        {
            
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            /*Create a Comnet node at specified node id (2)*/
            Comnet.Node UgvNode = new Comnet.Node(2);

            /*Construct class to hold all callbacks and behaviors*/
            ComnetCallbacks UgvCallbacks = new ComnetCallbacks();

            /*Create a link id variable to reference a created datalink*/
            sbyte link_id = 0;

            /*
            Register the methods of the callback class with Comnet
            Note that this is not a HARDWARE register. It passes the callback
            so the handler can execute it when the respective message is received
            */
            UgvNode.RegisterPingEvent(UgvCallbacks.OnPing);
            UgvNode.RegisterPongEvent(UgvCallbacks.OnPong);


            
            
            try
            {
                /*Add a new datalink to the Comnet session and establish an endpoint*/
                UgvNode.AddZigBeeDatalink(out link_id, 57600, "5");
                UgvNode.EstablishZigBeeEndpoint(link_id, 1, "0013A2004091798F");
            }
            catch(Exception err)
            {
                System.Console.WriteLine(err.ToString());
                System.Console.ReadKey();
                System.Environment.Exit(0);
            }
            
            

            /*Loop forever*/
            while (true)
            {
                System.Threading.Thread.Sleep(1000);
                UgvNode.SendPing(1, 0);

            }
        }
    }
}


