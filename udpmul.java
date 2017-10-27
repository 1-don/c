
/*****  udpchatclient.java ****/

import java.io.*;
import java.net.*;

public class udpchatclient
{
 public static void main(String args[]) throws IOException
 {
	 String message = null;
	 DatagramSocket cs = null; 
		 			
	 cs = new DatagramSocket();  
		  
	 byte[] receiveData = new byte[512];   
	 byte[] sendData  = new byte[512]; 
	 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));  
	 System.out.println(" UDP Client socket is created and waiting for server");
		
     InetAddress IPAddress = InetAddress.getByName("localhost"); 
  
	 int port = 9001;
		  
	 while(true)
	 {
		System.out.println("Client Says:");
						
		message = br.readLine();	
			 
		sendData = message.getBytes(); 
		  
		DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress,port); 
  
		cs.send(sendPacket);  
  
		DatagramPacket receivePacket =new DatagramPacket(receiveData, receiveData.length); 
  
		cs.receive(receivePacket); 
  
		message = new String(receivePacket.getData(), 0, receivePacket.getLength());  //myoperation = istream.readUTF();

		System.out.println("Server Says: "+message);
			 
	  }
			   
	}
}
/*
OUTPUT:
gescoe@slave12:~/Desktop$ javac udpchatclient.java 
gescoe@slave12:~/Desktop$ java udpchatclient
 UDP Client socket is created and waiting for server
Client Says:
hi
Server Says: good morning
Client Says:
bye
Server Says: bye
Client Says:
end

*/



/*****   udpchatserver.java  ****/


import java.io.*;
import java.net.*;

public class udpchatserver
{
  public static void main(String args[]) throws IOException 
  {
	 DatagramSocket ss = null; 
	 //ServerSocket serversocket = null; Socket socket =null;
			
	 ss = new DatagramSocket(9001);  
	 //serversocket = new ServerSocket(8000);
		  
	 byte[] receiveData = new byte[512]; 
	   //DataInputStream istream = new DataInputStream(socket.getInputStream());
	 byte[] sendData  = new byte[512]; 
	 //DataOutputStream ostream = new DataOutputStream(socket.getOutputStream());
	 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));   
	 System.out.println(" UDP Server socket is created and waiting for client");
		
	 while(true) 
	 { 
  		  
	  DatagramPacket receivePacket =new DatagramPacket(receiveData, receiveData.length); 
  
	  ss.receive(receivePacket); 
  
	  String message = new String(receivePacket.getData(), 0, receivePacket.getLength());  //myoperation = istream.readUTF();
	  System.out.println("Client Says: "+message);
	  if(message.equals("end")) break;
	  // To read from console
	  System.out.println("Enter Server Message:");
	  message = br.readLine();
		  
	  InetAddress IPAddress = receivePacket.getAddress(); 
  
	  int port = receivePacket.getPort(); 
		  
	  sendData = message.getBytes(); 
  
	  DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress,port); 
  
	  ss.send(sendPacket); 
	  //ostream.writeUTF(myoperation);
		 	 } 	
    ss.close();
    System.out.println("Server Stopped by User program");
  }
}

/********************************************
OUTPUT:
gescoe@gescoe-OptiPlex-3020:~/Desktop$ javac udpchatserver.java 
gescoe@gescoe-OptiPlex-3020:~/Desktop$ java udpchatserver
 UDP Server socket is created and waiting for client
Client Says: hi
Enter Server Message:
good morning          
bClient Says: bye
Enter Server Message:
bye
Client Says: end
Server Stopped by User program
gescoe@gescoe-OptiPlex-3020:~/Desktop$ 

***************************************/



