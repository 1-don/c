/**** Client_n.java  ***/


import java.io.*;
import java.net.*;

public class Client_n 
{
public static void main(String args[]) throws IOException
{
    InetAddress address=InetAddress.getLocalHost();
    Socket s1=new Socket("192.168.3.56", 4445); // You can use static final constant PORT_NUM
    String line=null;
    BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
    BufferedReader is=new BufferedReader(new InputStreamReader(s1.getInputStream()));
    PrintWriter os=new PrintWriter(s1.getOutputStream());     
    System.out.println("Client Address : "+address);
    System.out.println("Enter Data to echo Server ( Enter QUIT to end):");
    String response=null;
    try
    {
	line=br.readLine();
        while(line.compareTo("QUIT")!=0)
	    {
                os.println(line);
                os.flush();
                response=is.readLine();
                System.out.println("Server Response : "+response);
                line=br.readLine();
            }
      }
    catch(IOException e)
    {
     e.printStackTrace();
    System.out.println("Socket read Error");
    }
    finally
    {
        is.close();
	  os.close();
	  br.close();
	  s1.close();
                System.out.println("Connection Closed");
    }
}
}


/*************************************
OUTPUT:
gescoe@slave12:~/Desktop/gaurav $ javac Client_n.java
gescoe@slave12:~/Desktop/gaurav $ java Client_n
Client Address : slave12/192.168.3.88
Enter Data to echo Server ( Enter QUIT to end):
hii server
Server Response : hii 
ok bye
Server Response : ok bye

*************************************/


/****  Server_n2.java  ****/

import java.io.*;
import java.net.*;

public class Server_n2
{
   public static void main(String args[])
   {
    Socket s=null;
    ServerSocket ss2=null;
    System.out.println("Server Listening......");
    try
    {
        ss2 = new ServerSocket(4445); 
    }
    catch(IOException e)
    {
    e.printStackTrace();
    System.out.println("Server error");
    }
    while(true)
    {
        try
        {
            s= ss2.accept();
            System.out.println("connection Established");
            ServerThread st=new ServerThread(s);
            st.start();
        }
    catch(Exception e)
    {
        e.printStackTrace();
        System.out.println("Connection Error");
    }
    }
}
}
class ServerThread extends Thread
{  
    String line=null;
    BufferedReader  is = null;
    PrintWriter os=null;
    Socket s=null;
    public ServerThread(Socket s)
    {
        this.s=s;
    }
    public void run()
     {
    try
    {
        is= new BufferedReader(new InputStreamReader(s.getInputStream()));
        os=new PrintWriter(s.getOutputStream());
    }catch(IOException e)
    {
        System.out.println("IO error in server thread");
    }
    try 
    {
        line=is.readLine();
        while(line.compareTo("QUIT")!=0)
        {
            os.println(line);
            os.flush();
            System.out.println("Response to Client  :  "+line);
            line=is.readLine();
        }   
    } 
    catch (IOException e)
     {
        line=this.getName(); //reused String line for getting thread name
        System.out.println("IO Error/ Client "+line+" terminated abruptly");
    }
    catch(NullPointerException e)
    {
        line=this.getName(); //reused String line for getting thread name
        System.out.println("Client "+line+" Closed");
    }
    finally
    {    
    try
    {
        System.out.println("Connection Closing..");
        if (is!=null)
        {
            is.close(); 
            System.out.println(" Socket Input Stream Closed");
        }
        if(os!=null)
        {
            os.close();
            System.out.println("Socket Out Closed");
        }
        if (s!=null)
        {
        s.close();
        System.out.println("Socket Closed");
        }
        }
    catch(IOException ie)
    {
        System.out.println("Socket Close Error");
    }
    }//end finally
    }
}




/**************************************
gescoe@gescoe-OptiPlex-3020:~/Desktop/gaurav$ javac Server_n2.java
gescoe@gescoe-OptiPlex-3020:~/Desktop/gaurav$ java Server_n2
Server Listening......
connection Established
Response to Client  :  hii 
hello client
Response to Client  :  ok bye
******************************************/

