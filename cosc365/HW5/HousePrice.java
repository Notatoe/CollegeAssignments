// Noah Morris
// nmorri11

public class HousePrice
{
    // Person class that holds the needed variables and a constructor
    static class Person
    {
        String name;
        HouseColor color;
        int price;
        
        Person() {}
    }

    // enumerated HouseColor variable
    public enum HouseColor
    {
        RED,
        BLUE,
        GREEN,
        WHITE
    }

    // function for getting the year
    public static int getYear(HouseColor color)
    {
        // initializing the year because it would throw an error without it
        int year = 2010;

        // switch statement for the enumerated value to set the specific year
        switch(color)
        {
            case RED:
                year = 2010;
                break;
            case BLUE:
                year = 2011;
                break;
            case GREEN:
                year = 2012;
                break;
            case WHITE:
                year = 2013;
                break;
            default:
        }
        
        // return the year
        return year;
    }

    // function for getting the color
    public static String getColor(HouseColor color)
    {
        // initialized the new color so an error won't be thrown
        String newColor = "red";

        // switch statement with the enumerated value so that the color can be read in a string
        switch(color)
        {
            case RED:
                newColor = "red";
                break;
            case BLUE:
                newColor = "blue";
                break;
            case GREEN:
                newColor = "green";
                break;
            case WHITE:
                newColor = "white";
                break;
            default:
        }

        // returns the new color string
        return newColor;
    }

    public static void main(String[] args)
    {
        // error checks for being the correct size
        if(args.length % 3 != 0 || args.length < 3)
        {
            System.out.println("ERROR: Incorrect number of arguments (must be a multiple of 3 and greater than 0)");
            System.exit(0);
        }

        // initializes the array of Person objects
        Person []people;
        people = new Person[args.length / 3];

        // initializes the average cost and sets it to 0 to start
        double average = 0;

        // for loop for reading in the arguments into Person objects
        for(int i = 0; i < args.length; i += 3)
        {
            // temporary Person used for insertion
            Person temp = new Person();

            // sets the name
            temp.name = args[i];
            
            // sets the price and adds to the average
            temp.price = Integer.parseInt(args[i+1]);
            average += temp.price;
            
            // uses a switch statment to set the enumerated HouseColor value
            String tempColor = args[i+2];
            switch(tempColor.toLowerCase())
            {
                case "red":
                    temp.color = HouseColor.RED;
                    break;
                case "blue":
                    temp.color = HouseColor.BLUE;
                    break;
                case "green":
                    temp.color = HouseColor.GREEN;
                    break;
                case "white":
                    temp.color = HouseColor.WHITE;
                    break;
                default:
            }

            // inserts temp into the array
            people[i/3] = temp;
        }
        // makes the average the actual average cost by diving it by the amount of houses
        average = average / (args.length / 3);

        // prints out the average house price in the correct format
        System.out.printf("average house price = %,10.2f%n%n", average);

        // for loop that prints every person in the array
        for(int i = 0; i < people.length; i++)
        {
            // prints the name, price, and wether or not the price is greater than average
            System.out.printf("%-15s %,10d %b%n", people[i].name, people[i].price, people[i].price > average);

            // gets the year and color in string format
            int year = getYear(people[i].color);
            String color = getColor(people[i].color);
            
            // prints the last line with the correct color and year
            System.out.printf("This %s house was built in the year %d%n", color, year);
        }
    }
}