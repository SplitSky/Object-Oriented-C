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

/// abstract class
class shape {
    // friend std::ostream& operator<<(std::ostream &os, shape &shape);
    // friend std::ifstream& operator>>(std::ifstream &os, shape &shape);
    protected:
        std::vector<double> dimensions;
        std::string name{"shape"};
    public:
        shape() = default;
        shape(std::vector<double> init_dimensions, std::string init_name) : dimensions{init_dimensions}, name{init_name} {}
        virtual ~shape() {}

        std::string show_name() {
            return this->name;
        }
        void set_name(std::string name) {
            this->name = name;
        }

        virtual double calc_area() {return 0;};
        virtual double calc_volume() {return 0;}
};

class shape_2D: public shape {
    public:
        shape_2D() :shape{} {};
        shape_2D(std::vector<double> init_dimensions, std::string name) : shape{init_dimensions,name} {}
        ~shape_2D() {}
        virtual double calc_area() {
            return dimensions[0]*dimensions[1];
        }
};

class shape_3D: public shape_2D {
    public:
        shape_3D() : shape_2D{} {}
        shape_3D(std::vector<double> init_dimensions, std::string name) : shape_2D{init_dimensions, name} {}
        virtual double calc_volume() {
                return dimensions[0]*dimensions[1]*dimensions[2];
        }
};

class square: public shape_2D {
    // all works
    public:
        square(): shape_2D{} {}
        square(std::vector<double> dimensions) : shape_2D{dimensions, "square"} {}
        ~square() {}
        virtual double calc_area() {
            return pow(dimensions[0], 2);
        }
};

class rectangle: public shape_2D {
    public:
        rectangle(): shape_2D{} {}
        rectangle(std::vector<double> dimensions) : shape_2D{dimensions, "rectangle"} {}
        virtual ~rectangle() {};
};

class cuboid: public shape_3D {
    public:
        cuboid(): shape_3D{} {}
        cuboid(std::vector<double> dimensions) : shape_3D{dimensions, "cuboid"} {}
        ~cuboid() {};
        virtual double calc_area() {
            double area{0};
            area += 2*dimensions[0]*dimensions[1];
            area += 2*dimensions[1]*dimensions[2];
            area += 2*dimensions[0]*dimensions[2];
            return area;
        }
        // use the default volume function for shape_3D
};


class cube: public shape_3D {
    public:
        cube(): shape_3D{} {}
        cube(std::vector<double> dimensions) : shape_3D{dimensions, "cube"} {}
        virtual double calc_area() {
            return 6*pow(dimensions[0],2);

        }

        virtual double calc_volume() {
            return pow(dimensions[0],3);
        }

};

class circle: public shape_2D {
    public:
        circle(): shape_2D{} {}
        circle(std::vector<double> dimensions) : shape_2D{dimensions, "circle"} {}
        ~circle() {}
        virtual double calc_area() {
            return  M_PI*pow(dimensions[0],2);
        }
};

class sphere: public shape_3D {
    public:
        sphere(): shape_3D{} {}
        sphere(std::vector<double> dimensions) : shape_3D{dimensions, "sphere"} {}
        ~sphere() {}
        virtual double calc_area() {
            return M_PI*4.0*pow(dimensions[0],2);
        }

        virtual double calc_volume() {
            return M_PI*4.0/3.0*pow(dimensions[0],3);
        }
};

class ellipse: public shape_2D {
    public:
        ellipse(): shape_2D{} {}
        ellipse(std::vector<double> dimensions): shape_2D{dimensions, "ellipse"} {}
        ~ellipse() {}
        virtual double calc_area() {
            return M_PI * shape_2D::calc_area();
        }
};

class ellipsoid: public shape_3D {
    private:
        const double ellipsoid_constant{1.6075};
    public:
        ellipsoid() : shape_3D{} {}
        ellipsoid(std::vector<double> dimensions): shape_3D{dimensions, "ellipsoid"} {}
        virtual double calc_volume() {
            return 4.0 / 3.0 * M_PI * shape_3D::calc_volume();
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

        virtual double calc_volume() {
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
