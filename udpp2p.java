/****  udpclient.java ***/ 
  
import java.io.*;
import java.net.*;

public class udpclient
{
  public static void main(String args[]) throws IOException
  {
	 String message = null;
	 DatagramSocket cs = null; 
			
	 cs = new DatagramSocket();  
 	  
	 byte[] receiveData = new byte[512];   

	 byte[] sendData  = new byte[512]; 
			  
	 System.out.println(" UDP Client socket is created and waiting for server");
		
     InetAddress IPAddress = InetAddress.getByName("localhost"); 
  
     int port = 9000;
		  
	 message = "Hello Server";
  
	 sendData = message.getBytes(); 
  
	 DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress,port); 
  
	 cs.send(sendPacket); 
	   
	 DatagramPacket receivePacket =new DatagramPacket(receiveData, receiveData.length); 
  
	 cs.receive(receivePacket); 
  
	 message = new String(receivePacket.getData());  
	
	 System.out.println("Server Says: "+message);
		
	}
}
/*
OUTPUT:
gescoe@slave12:~/Desktop$ javac udpclient.java 
gescoe@slave12:~/Desktop$ java udpclient
 UDP Client socket is created and waiting for server
Server Says: Thanks
gescoe@slave12:~/Desktop$ 
*/



/****  udpserver.java ****/


import java.io.*;
import java.net.*;

public class udpserver
{
 public static void main(String args[]) throws IOException 
 {
    DatagramSocket ss = null; 
    //ServerSocket serversocket = null; Socket socket =null;
			
	ss = new DatagramSocket(9000); 
	//serversocket = new ServerSocket(8000);
		  
	byte[] receiveData = new byte[512];  
	//DataInputStream istream = new DataInputStream(socket.getInputStream());
	byte[] sendData  = new byte[512]; 
	//DataOutputStream ostream = new DataOutputStream(socket.getOutputStream());
		  
	System.out.println(" UDP Server socket is created and waiting for client");
		
	while(true) 
	 { 
  	   DatagramPacket receivePacket =new DatagramPacket(receiveData, receiveData.length); 
  
	   ss.receive(receivePacket); 
  
	   String message = new String(receivePacket.getData()); 
	   //myoperation = istream.readUTF();

	   System.out.println("Client Says: "+message);
		
	   InetAddress IPAddress = receivePacket.getAddress(); 
  
	   int port = receivePacket.getPort(); 
		  
	   message = "Thanks";
  
	   sendData = message.getBytes(); 
  
	   DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress,port); 
  
	   ss.send(sendPacket); //ostream.writeUTF(myoperation);
		  	 	
	   if(message.equals("Thanks")) break;
	  } 	
	 ss.close();
	 System.out.println("Server Stopped by User program");
  }
}


/*****************************
OUTPUT:
 gescoe@gescoe-OptiPlex-3020:~/Desktop$ javac udpserver.java 
gescoe@gescoe-OptiPlex-3020:~/Desktop$ java udpserver
 UDP Server socket is created and waiting for client
Client Says: Hello Server
Server Stopped by User program
gescoe@gescoe-OptiPlex-3020:~/Desktop$ 

********************************/
	 
