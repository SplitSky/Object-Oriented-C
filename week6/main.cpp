// Object oriented C++ - Assignment 6 - Classes
// Tomasz Neska
// 22/04/2021
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<array>
#include<iterator>
#include<cstring>
#define _USE_MATH_DEFINES

// things to do
// 1. Abstract class used as an interface for all shapes
// 2. Abstract derived class for a) 2D shapes b) 3D shapes
// 3. Derived classes for at least 4 2D shapes (rectangle, square ellipse, circle)
// 4. Derived classes for at least 4 3D shapes (cuboid, cube, ellipsoid, sphere)
// 5. Additional ingeritance for specialisation ("is a")
// 6. Constructors and virtual destructors
// 7. Pure virtual fuctions to return area and volume (can be zero for 2D shapes)
// Main must:
// Implement an vector of at least 8 base class pointers, each pointing to a different shape
// Output the area and volume for 3D shapes
// Clean up by deleting objects and arrays when finished

// abstract class
class shape {
    // friend std::ostream& operator<<(std::ostream &os, shape &shape);
    // friend std::ifstream& operator>>(std::ifstream &os, shape &shape);
    protected:
        std::vector<double> dimensions;
        std::string name{"shape"};
    public:
        shape() = default;
        shape(std::vector<double> init_dimensions, std::string init_name) : dimensions{init_dimensions}, name{init_name} {
        }
        virtual ~shape() {}

        virtual double calc_area() {
            return dimensions[0]*dimensions[1];
        }

        virtual double calc_volume() {
            if (this->dimensions.size() < 2) {
                // for 2D shapes return 0
                return 0;
            } else {
                double volume{1};
                for (size_t i{0}; i<3; i++) {volume *= this->dimensions[i];}
                return volume;
            }
        }
        std::string show_name() {
            return this->name;
        }
};

class square: public shape {
    // all works
    public:
        square(): shape{} {}
        square(std::vector<double> dimensions) : shape{dimensions, "square"} {}
        ~square() {}
        virtual double calc_area() {
            return pow(dimensions[0], 2);
        }
};

class rectangle: public shape {
    public:
        rectangle(): shape{} {}
        rectangle(std::vector<double> dimensions) : shape{dimensions, "rectangle"} {}
        virtual ~rectangle() {};
        double calc_volume() {return 0;}
};

class cuboid: public rectangle {
    public:
        cuboid(): rectangle{} {}
        cuboid(std::vector<double> dimensions) : rectangle{dimensions} {this->name = "cuboid";}
        ~cuboid() {};
        virtual double calc_area() {
            double area{0};
            area += 2*dimensions[0]*dimensions[1];
            area += 2*dimensions[1]*dimensions[2];
            area += 2*dimensions[0]*dimensions[2];
            return area;
        }
        // use the default volume function for shape
};


class cube: public square {
    public:
        cube(): square{} {}
        cube(std::vector<double> dimensions) : square{dimensions} {this->name = "cube";}
        virtual double calc_area() {
            return 6*square::calc_area();
        }

        virtual double calc_volume() {
            return square::calc_area()*dimensions[0];
        }

};

class circle: public shape {
    public:
        circle(): shape{} {}
        circle(std::vector<double> dimensions) : shape{dimensions, "circle"} {}
        ~circle() {}
        virtual double calc_area() {
            return  M_PI*pow(dimensions[0],2);
        }
};

class sphere: public shape {
    public:
        sphere(): shape{} {}
        sphere(std::vector<double> dimensions) : shape{dimensions, "sphere"} {}
        ~sphere() {}
        virtual double calc_area() {
            return M_PI*4.0*pow(dimensions[0],2);
        }

        virtual double calc_volume() {
            return M_PI*4.0/3.0*pow(dimensions[0],3);
        }
};

class ellipse: public shape {
    public:
        ellipse(): shape{} {}
        ellipse(std::vector<double> dimensions): shape{dimensions, "ellipse"} {}
        ~ellipse() {}
        virtual double calc_area() {
            return M_PI * shape::calc_area();
        }
};

class ellipsoid: public ellipse {
    private:
        const double ellipsoid_constant{1.6075};
    public:
        ellipsoid() : ellipse{} {}
        ellipsoid(std::vector<double> dimensions): ellipse{dimensions} {this->name = "ellipsoid";}
        virtual double calc_volume() {
            return 4.0 / 3.0 * M_PI * ellipse::calc_volume();
        }
        ~ellipsoid() {};
        virtual double calc_area() {
            // approximate with about 2% error
            return 4*M_PI*pow((dimensions[0]*dimensions[1] + dimensions[0]*dimensions[2] + dimensions[1]*dimensions[2])/3 , 1/ellipsoid_constant);
        }
};

class prism {
    private:
        double volume{0};
        double depth;
        shape* shape_pointer;
        int type{0};
    public:
        prism() {}
        prism(shape* shape_pointer, double depth) : depth{depth}, shape_pointer{shape_pointer} {}

        ~prism() {};

        double calc_volume() {
            return shape_pointer->calc_area()*depth;
        }
};

int main() {
    // due to using vectors the data doesn't have to be garbage collected as the vectors unassign memory automatically 
    std::vector<double> data = {2};
    std::vector<double> data2 = {5,6};
    std::vector<double> data3 = {10,11,12};
   

    shape *shapes_array[10];
    shapes_array[0] = new square{data};
    shapes_array[1] = new cube{data};
    shapes_array[2] = new circle{data};
    shapes_array[3] = new sphere{data};
    shapes_array[4] = new cuboid{data3};
    shapes_array[5] = new ellipse{data2};
    shapes_array[6] = new ellipsoid{data3};
    shapes_array[7] = new rectangle{data2};
    
    prism prism1{shapes_array[0],2};
    prism prism2{shapes_array[2], 2};


    std::cout << std::endl;
    std::cout << "Showing the use of the base class pointers" << std::endl;

    for (size_t i{}; i<8; i++) {
        std::cout << "Calculating the area for "<< shapes_array[i]->show_name()<< ": "<< shapes_array[i]->calc_area() << std::endl;
        std::cout << "Calculating the volume for "<< shapes_array[i]->show_name() << ": " << shapes_array[i]->calc_volume() << std::endl;
    }

    std::cout << "Calculating volumes for prisms" << std::endl;
    std::cout << "Prism with square face volume: " << prism1.calc_volume() << std::endl;
    std::cout << "Cylinder volume: " << prism2.calc_volume() << std::endl;


    // clean up
    // no need to clean the vector memory as it does it automatically when it's out of scope. No memory leaks
    delete shapes_array[0];
    delete shapes_array[1];
    delete shapes_array[2];
    delete shapes_array[3];
    delete shapes_array[4];
    delete shapes_array[5];
    delete shapes_array[6];
    delete shapes_array[7];
    return 0;
}
