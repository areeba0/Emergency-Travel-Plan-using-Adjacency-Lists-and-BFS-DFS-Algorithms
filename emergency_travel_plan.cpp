#include <iostream>
#include <iomanip>
#include <cmath> 
// Include cmath for std::abs
using namespace std;

// A large constant representing infinity
const int INFINITY_COST = 1e9;

//  A node class to show travel routes
class Travel_Node 
{
public:
    int des;
    int cost;
    Travel_Node* next;
     
     // Default constructor
    Travel_Node()
    {
         des = 0;
         cost = 0;
         next = nullptr;
    }
   
    // Parameterized constructor
    Travel_Node(int _destination, int _cost, Travel_Node* _next)
    {
         des  = _destination ;
         cost = _cost ;
         next = _next ;
    }
};

// A Node class for showing cities
class City_Node
{
public:

    Travel_Node* road_routes;
    int id;
    bool visited;

 // Default constructor
    City_Node() 
    {
         id = 0 ;
         visited = false ;
         road_routes = nullptr ;
    }
    
   // Parameterized constructor
    City_Node(int _id) 
    {
         id = _id;
         visited = false ;
         road_routes = nullptr ;
         
    }
};

// Controller class to manage the traveler's journey
class Traveler_Controller
{
private:

    Travel_Node** aerial_routes;
    int* path;
    int num_cities;
    City_Node* cities;

      // Initialize the graph with road routes 
     // and aerial routes
   void initialize_Graph()
   {
     // Initializing road routes for each city
    int city_index = 0;
    do
    {
        cities[city_index].road_routes = nullptr;
        ++city_index;
    } while (city_index < num_cities);

    // Adding  road routes and aerial routes 
    // to the adjacency list
    city_index = 0;
    do
    {
        int source_city = city_index;
        int road_index = 1;
        do
        {   
             // Creating road routes with costs
             // based on distance
            int cost = std::abs((city_index + road_index) - city_index);
            cities[source_city].road_routes = new Travel_Node(city_index + road_index, cost, cities[source_city].road_routes);
            ++road_index;
            
        } while (road_index <= 6 && city_index + road_index < num_cities);

        //  checking if an aerial route is available
        // then add it to the adjacency list
        if (has_Aerial_Route(city_index))
        {
            int cost = std::abs(aerial_routes[city_index]->des - city_index);
            cities[source_city].road_routes = new Travel_Node(aerial_routes[city_index]->des, cost, cities[source_city].road_routes);
        }

        ++city_index;
    } while (city_index < num_cities);
}
    
    // Applying breadth-first search to find the minimum days for travel

    int bfs(bool cost_optimization)
    {
        int days = 0;
        int current_city = 0;

        int path_index = 0;
        do
        {
            int next_city = -1;

            if (has_Aerial_Route(current_city)) 
            {
                 // Moving to the next city using the aerial route
                next_city = aerial_routes[current_city]->des;
                cities[next_city].visited = true;
            } 
            else 
            {
                Travel_Node* current = cities[current_city].road_routes;
                bool road_available = false;

                if (cost_optimization) 
                {
                       // Optimize for cost
                      // find the minimum cost road route
                    int min_cost = INFINITY_COST;
                    do 
                    {
                        if (!cities[current->des].visited && current->cost < min_cost) 
                        {
                            next_city = current->des;
                            min_cost = current->cost;
                            road_available = true;
                            
                        }
                        current = current->next;
                        
                    } while (current);
                } 
                else 
                {
                     // Optimize for speed
                     // choosing the 1st available road route
                    int road_index = 0;
                    do 
                    {
                        if (!cities[current->des].visited)
                        {
                            next_city = current->des;
                            cities[next_city].visited = true;
                            road_available = true;
                            break;
                        }
                        current = current->next;
                        ++road_index;
                    } while (road_index < 6 && current);
                }

                 // Handling  the case if there are no road routes available
                if (!road_available) 
                {
                    cout << "Stuck at City " << current_city << ". Unable to reach the destination.\n";
                    return -1;
                }
            }

            ++days;
            path[path_index++] = next_city;

             // Searching the next unvisited city
            int city_index = current_city + 1;
            do {
              
                if (!cities[city_index].visited)
                {
                    current_city = city_index;
                    break;
                }
                
                ++city_index;
            } while (city_index < num_cities);

            if (city_index == num_cities)
            {
                  // Break if all cities are visited
                  break;
            }
        } while (current_city != num_cities - 1);


        // Printing the path taken by the traveler
        cout << "Path taken by the traveler: ";
        int index = 0;
        do
        {
            cout << "City " << path[index] + 1 << " ";
            ++index;
            
        } while (index < path_index);
        cout << "\n";

        return days;
    }
    
    //  using bool to check if a city has an aerial route
    bool has_Aerial_Route(int city)
    {
        return aerial_routes[city] != nullptr;
    }


public:
// constructor
    Traveler_Controller(int _num_cities, int _num_aerial_routes, Travel_Node** _aerial_routes)
        : num_cities(_num_cities)
        {
        cities = new City_Node[num_cities];
        aerial_routes = _aerial_routes;
        path = new int[num_cities];

         // Initialize the graph with aerial routes and road routes
        initialize_Graph();
    }
    
    // destructor
    ~Traveler_Controller()
    {
        delete[] cities;
        delete[] path;
    }
   
   // selection mode for choosing optimization strategy
    void interactive_Mode() 
    {
        int choice;
        cout << "~~~~~~ *MENU* ~~~~~~" << endl;
        cout << "Choose a strategy:\n";
        cout << "1. Optimize for Speed\n";
        cout << "2. Optimize for Cost\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: {
                cout << "\n=======================================================\n";
                cout << "Speed optimization strategy selected.\n";
                cout << "Traversing using the Fastest Routes:\n";

                int city_index = 0;
                do
                {
                    cities[city_index].visited = false;
                    ++city_index;
                } while (city_index < num_cities);

                   // speed optimization
                  // Calculate minimum days for travel for speed 
                int min_days_speed = bfs(false);
                cout << "Minimum days required for travel with speed optimization: " << min_days_speed << "\n";
                cout << "=======================================================\n";
                break;
            }

            case 2: 
            {
                cout << "\n=======================================================\n";
                cout << "Cost optimization strategy selected.\n";
                cout << "Traversing using the Most Cost-Effective Routes:\n";

                int city_index = 0;
                do 
                {
                    cities[city_index].visited = false;
                    ++city_index;
                } while (city_index < num_cities);

                 // cost optimization
                 // Calculate minimum days for travel for cost
                int min_days_cost = bfs(true);
                
                cout << "Minimum days required for travel with cost optimization: " << min_days_cost << "\n";
                cout << "=======================================================\n";
                break;
            }

            default:
                cout << "Invalid choice. Using the default strategy.\n";
                break;
        }
    }
    
    // printing the graph in Adjacency list form
    void print_Graph() 
    {
        cout << "\n=======================================================\n";
        cout << "Graph Representation (Adjacency List):\n";
        int city_index = 0;

        do 
        {
            cout << "City " << cities[city_index].id << ": { ";

            Travel_Node* road_route = cities[city_index].road_routes;

            do
            {
                cout << "City " << road_route->des + 1 << " ";
                road_route = road_route->next;
            } while (road_route);

            if (has_Aerial_Route(city_index)) 
            {
                cout << "(Aerial) City " << aerial_routes[city_index]->des + 1 << " ";
            }

            cout << "}\n";
            ++city_index;
        } while (city_index < num_cities);
        cout << "=======================================================\n\n";
    }
    
     // Calculate the minimum days for travel 
     //based on the chosen optimization strategy
     // which is speed or cost 
    int calculate_Min_Days(bool cost_optimization)
    {
        return bfs(cost_optimization);
    }

};


int main() 
{
     cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
     cout << "                  EMERGENCY TRAVEL PLAN                       "<< endl;
     cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
     cout<< endl;
    int num_test_cases;

    // Getting the number of test cases from user
    while (true)
    {
        cout << "Enter the number of test cases: ";

        int input;
        if (cin >> input && input > 0) 
        {
            num_test_cases = input;
            
            break;
        } 
        else
        {
            cin.clear();
            while (cin.get() != '\n')
                ;
            cout << "Error !!! Invalid input. Please enter a valid integer greater than 0.\n";
        }
    }

    int test_case = 0;
    do 
    {
        int num_cities;
        int num_aerial_routes;

        cout << "\n=======================================================\n";
        cout << "Test Case " << test_case + 1 << ":\n";

        // Getting the number of cities for the current test case number from user
        while (true)
        {
            cout << "Enter the number of cities : ";

            int input;
            if (cin >> input && input > 0) {
                num_cities = input;
                break;
            }
            else 
            {
                cin.clear();
                while (std::cin.get() != '\n')
                    ;
                cout << "Error !!! Invalid input. Please enter a valid integer greater than 0.\n";
            }
        }

          // Get the number of aerial routes from the user
         // for current test case number
        while (true)
        {
            cout << "Enter the number of aerial routes: ";
            int input;
            if (cin >> input && input >= 0)
            {
                num_aerial_routes = input;
                break;
            } 
            else 
            {
                cin.clear();
                while (cin.get() != '\n')
                    ;
                cout << "Error !!! Invalid input. Please enter a valid integer greater than or equal to 0.\n";
            }
        }
        
        // Initializing the array to store aerial routes
        Travel_Node** aerial_routes = new Travel_Node*[num_cities];
        int i = 0;
        
        do 
        {
            aerial_routes[i] = nullptr;
            ++i;
        } while (i < num_cities);

        // Getting the source and destination of aerial routes from user
        cout << "Enter the source and destination of aerial routes:\n";
        int j = 0;
        do 
        {
            int source;
            int destination;
            cout << "Aerial Route " << j + 1 << ": ";
            cin >> source >> destination;

            aerial_routes[source] = new Travel_Node(destination, 0, aerial_routes[source]);
            ++j;
        } while (j < num_aerial_routes);

        Traveler_Controller traveler_controller(num_cities, num_aerial_routes, aerial_routes);
        
          // Printing  the graph 
        traveler_controller.print_Graph();
        
           //  choosing optimization strategy
        traveler_controller.interactive_Mode();

        // Calculating and printing the minimum days required for travel (normal)
        // without speed or cost
        int min_days;
        min_days = traveler_controller.calculate_Min_Days(false);

        cout << "Minimum days required for travel: " << min_days << endl;
        
        // Releasing memory allocated ( for aerial routes )
        i = 0;
        do 
        {
            Travel_Node* current = aerial_routes[i];
            do
            {
                Travel_Node* temp = current;
                current = current->next;
                delete temp;
            } while (current);
            ++i;
        } while (i < num_cities);
        delete[] aerial_routes;

        ++test_case;
    } while (test_case < num_test_cases);

    return 0;
}
