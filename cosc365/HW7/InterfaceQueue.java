// Noah Morris
// nmorri11

import java.io.*;
import java.util.*;

public class InterfaceQueue
{
    // interface for a Queue and its fucntion headers
    static interface Queue<Object>
    {
        void push(Object o);
        Object pop();
        Object peek();
        void loop();
        boolean isEmpty();
        int length();
    }

    // Class for ArrayQueue, the arraylist style queue
    public static class ArrayQueue implements Queue<Integer>
    {
        // The arraylist that holds the integer values
        ArrayList<Integer> arrayQueue = new ArrayList<Integer>();

        // Function for adding an integer to the back of the queue
        public void push(Integer data)
        {
            this.arrayQueue.add(data);
        }

        // Function for removing the head from the queue and returning it
        public Integer pop()
        {
            if(this.isEmpty())
                return null;
            
            Integer temp = this.arrayQueue.get(0);
            this.arrayQueue.remove(0);
            return temp;
        }
        
        // Function for just returning the head of the queue
        public Integer peek()
        {
            return this.arrayQueue.get(0);
        }

        // Function for moving the head of the queue to the back
        public void loop()
        {
            Integer temp = this.arrayQueue.get(0);
            this.arrayQueue.remove(0);
            this.arrayQueue.add(temp);
        }

        // Function that returns true if the queue is empty, false if otherwise
        public boolean isEmpty()
        {
            return this.arrayQueue.isEmpty();
        }

        // Function for returning the amount of indexes within the queue
        public int length()
        {
            return this.arrayQueue.size();
        }
    }

    // Class for Node objects that are used within the linked list style queue
    public static class Node<Object>
    {
        // Includes the data and the next node
        Object data;
        Node<Object> next;

        // Constructor
        public Node(Object data)
        {
            this.data = data;
        }
    }

    // Class for LinkListQueue, the linked list style queue
    public static class LinkListQueue implements Queue<Node<String>>
    {
        // Two nodes for easy access to the front and back of the queue
        Node<String> head;
        Node<String> tail;

        // Function for adding an integer to the back of the queue
        public void push(Node<String> data)
        {
            // If the list is empty set both head and tail to the data
            if(this.isEmpty())
            {
                this.head = data;
                this.tail = data;
            }
            // else append it to the end and set tail to the new node
            else
            {
                this.tail.next = data;
                this.tail = this.tail.next;
            }
        }

        // Function for removing the head from the queue and returning it
        public Node<String> pop()
        {
            // return null if theres nothing to pop
            if(this.isEmpty())
                return null;
            
            // saves the head node before removing it then returning it after the head has been removed
            Node<String> temp = this.head;
            this.head = this.head.next;
            return temp;
        }

        // Function for just returning the head of the queue
        public Node<String> peek()
        {
            return this.head;
        }

        // Function for moving the head of the queue to the back
        public void loop()
        {
            // pops and pushes the head node for convienience
            Node<String> temp = this.pop();
            this.push(temp);
        }

        // Function that returns true if the queue is empty, false if otherwise
        public boolean isEmpty()
        {
            //if head is null, the queue is empty
            if(this.head == null)
                return true;
            return false;
        }

        // Function for returning the amount of indexes within the queue
        public int length()
        {
            // return 0 if empty
            if(this.isEmpty())
                return 0;
            
            // set current to head and num to 1 since there is atleast 1 node
            Node current = this.head;
            int num = 1;

            // loop through and return the amount of nodes in the list by counting all of the nodes until the tail
            while(true)
            {
                if(current.next == null)
                    return num;
                current = current.next;
                num++;
            }
        }
    }

    public static void main(String[] args) throws IOException
    {
        // initializes the two queues
        ArrayQueue ints = new ArrayQueue();
        LinkListQueue nonInts = new LinkListQueue();

        // sets up for reading in the RandomNumbers.txt file
        FileReader inputFile = new FileReader("RandomNumbers.txt");
        BufferedReader reader = new BufferedReader(inputFile);
        String line = reader.readLine();

        // reads in the lines of the input file using a catch and try statement for if the line can be parsed as a string or not
        while(line != null)
        {
            try
            {
                // added to the ints array queue
                ints.push(Integer.parseInt(line));
            }
            catch (NumberFormatException e)
            {
                // added to the non-int list queue
                Node<String> nonInt = new Node<String>(line);
                nonInts.push(nonInt);
            }

            // traverses to next line
            line = reader.readLine();
        }
        // closes the input file
        reader.close();

        // prints out how many integers and non-integers are in the file
        System.out.printf("Number of Integers: %d%n", ints.length());
        System.out.printf("Number of non-Integers: %d%n", nonInts.length());
    
        // opens the output file and sets the current iteration to 1
        PrintWriter output = new PrintWriter("output.txt");
        int iteration = 1;

        // while the ints array queue is not empty
        while(!ints.isEmpty())
        {
            // sets sum to 0 and temp to the head of ints
            int sum = 0;
            int temp = ints.peek();

            // sums up every digit of temp
            while(temp != 0)
            {
                sum += temp % 10;
                temp = temp / 10;
            }
            
            // loops through ints for the amount of the sum of digits from peek
            for(int i = 0; i < sum; i++)
            {
                ints.loop();
            }
            
            // pops the most current head of ints and divides by 1000
            temp = ints.pop() / 1000;

            // loops through nonInts the amount specified by temp
            for(int i = 0; i < temp; i++)
            {
                nonInts.loop();
            }

            // prints the current head node's data in non-ints to the output file
            output.printf("%s%n", nonInts.peek().data);

            // pops ints for every iteration passed
            for(int i = 0; i < iteration; i++)
            {
                ints.pop();
            }

            // increases the iteration count
            iteration++;
        }
        // closes the output file
        output.close();
    }
}
