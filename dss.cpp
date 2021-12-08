#include <cstdlib>


#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

// including the GaloisFiniteField
#include "GaloisFiniteField.hpp"



namespace utils
{    
    float frand()
    {
        static float norm = 1.0f / (float)RAND_MAX;
        return (float)rand()*norm;
    }
    
    long long int irand(long long int min, long long int max)
    {
        return min+(long long int)(frand()*(float)(max-min));
    }
}



//Elliptic Curve Cryptography

    /*
        Elliptic Curve over a finite field of order P:
        y^2 mod P = x^3 + ax + b mod P
    */



namespace EllipCurv
{    

    template<long long int P>

    // Elliptic Curve Customized Class
    class ElliptCurv_cus_class
    {
        public:

            // Galios Finite Field type
            typedef GaloisFiniteField<P> finite_field;

            //cout << finite_field;
            class Point
            {
                friend class ElliptCurv_cus_class<P>;
                typedef GaloisFiniteField<P> finite_field;

                // Defining x and y values :
                finite_field xvalue_, yvalue_;
                ElliptCurv_cus_class *ec_;

                // Doubling multiplier
                // multiplies acc by m as a series of "2*acc's"
                void addDouble(long long int m, Point& acc)
                { 
                    if ( m > 0 )
                    {
                        Point r = acc;
                        for ( long long int n=0; n < m; ++n )
                        {
                            r += r;     // doubling step
                        }
                        acc = r;
                    }        
                }
                // Doubling multiplier
                // multiplies a by k by expanding in multiplies by 2
                // a is also an accumulator that stores the intermediate results
                // between the "1s" of the binary form of the input scalar k
                Point scalarMultiply(long long int k, const Point& a)
                {
                    Point acc = a;
                    Point res = Point(0,0,*ec_);
                    long long int i = 0, j = 0;
                    long long int b = k;
                    
                    while( b )
                    {
                        if ( b & 1 )
                        {
                            // bit is set; acc = 2^(i-j)*acc
                            addDouble(i-j,acc);
                            res += acc;           
                            j = i;  // last bit set
                        }
                        b >>= 1;
                        ++i;
                    }
                    //cout << res;
                    return res;
                }
                // adding two points on the curve
                void add(finite_field x1, finite_field y1, finite_field x2, finite_field y2, finite_field & xR, finite_field & yR) const
                {
                                    //cout << x1<< y1;                    
                    if ( x1 == 0 && y1 == 0 ) 
                    {
                        xR = x2;
                        yR = y2;
                        return;
                    }
                    if ( x2 == 0 && y2 == 0 )
                    {
                        xR = x1;
                        yR = y1;
                        return;
                    }
                    if ( y1 == -y2 ) 
                    {
                        xR = yR = 0;
                        return;
                    }
                    //cout << xR<< yR;
                                            
                    // the additions
                    finite_field s;                                                
                    if ( x1 == x2 && y1 == y2 )
                    {
                        //2P                          
                        s = (3*(x1.i()*x1.i()) + ec_->a()) / (2*y1);
                    //cout << s;
                        xR = ((s*s) - 2*x1);                            
                    }
                    else
                    {   
                        //P+Q                            
                        s = (y1 - y2) / (x1 - x2);
                        xR = ((s*s) - x1 - x2);
                    }
                    
                    if ( s != 0 )
                    {
                        yR = (-y1 + s*(x1 - xR));
                    }
                    else
                    {
                        xR = yR = 0;
                    }           
                }
                
                //cout << xR<< yR;

                Point(long long int x, long long int y)
                : xvalue_(x),
                    yvalue_(y),
                    ec_(0)
                {}
                                
                Point(long long int x, long long int y, ElliptCurv_cus_class<P> & ElliptCurv_cus_class)
                    : xvalue_(x),
                    yvalue_(y),
                    ec_(&ElliptCurv_cus_class)
                {}
                
                Point(const finite_field& x, const finite_field& y, ElliptCurv_cus_class<P> & ElliptCurv_cus_class)
                    : xvalue_(x),
                    yvalue_(y),
                    ec_(&ElliptCurv_cus_class)
                {}

            public:                    
                static Point ONE;

                // copy ctor
                Point(const Point& righthandside)
                {
                    //cout << 
                    xvalue_ = righthandside.xvalue_;
                    yvalue_ = righthandside.yvalue_;
                    ec_ = righthandside.ec_;
                     //cout << xvalue_<< yvalue_;
                }
                // assignment
                Point& operator=(const Point& righthandside)
                {
                    xvalue_ = righthandside.xvalue_;
                    yvalue_ = righthandside.yvalue_;
                    ec_ = righthandside.ec_;
                    return *this;
                }
                // access x component as element of Fp
                finite_field x() const { return xvalue_; }
                // access y component as element of Fp
                finite_field y() const { return yvalue_; }

                unsigned long long int Order(unsigned long long int maxPeriod = ~0) const

                // calculate the order of this point by brute-force additions
                // so maxPeriod should probably be set to something sensible...
                {
                    Point r = *this;
                    unsigned long long int n = 0;
                    while( r.xvalue_ != 0 && r.yvalue_ != 0 )
                    {
                        ++n;
                        r += *this;
                        if ( n > maxPeriod ) break;
                    }
                    // cout<< n;
                    return n;
                }
                // negate
                Point operator-()
                {
                    return Point(xvalue_,-yvalue_);
                }                                        
                // ==
                friend bool operator==(const Point& lhs, const Point& righthandside)
                {
                    return (lhs.ec_ == righthandside.ec_) && (lhs.xvalue_ == righthandside.xvalue_) && (lhs.yvalue_ == righthandside.yvalue_);
                }
                // !=
                friend bool operator!=(const Point& lhs, const Point& righthandside)
                {
                    return (lhs.ec_ != righthandside.ec_) || (lhs.xvalue_ != righthandside.xvalue_) || (lhs.yvalue_ != righthandside.yvalue_);
                }                    
                // a + b         
                friend Point operator+(const Point& lhs, const Point& righthandside)
                {       
                    finite_field xR, yR;
                    lhs.add(lhs.xvalue_,lhs.yvalue_,righthandside.xvalue_,righthandside.yvalue_,xR,yR);
                    return Point(xR,yR,*lhs.ec_);    
                }
                // a * long long int
                friend Point operator*(long long int k, const Point& righthandside)
                {
                    return Point(righthandside).operator*=(k);
                }
                // +=
                Point& operator+=(const Point& righthandside)
                {   
                    add(xvalue_,yvalue_,righthandside.xvalue_,righthandside.yvalue_,xvalue_,yvalue_);
                    return *this;  
                }
                // a *= long long int
                Point& operator*=(long long int k)
                {
                    return (*this = scalarMultiply(k,*this));
                }                    
                // ostream handler: print this point
                friend ostream& operator <<(ostream& os, const Point& p)
                {
                    return (os << "(" << p.xvalue_ << ", " << p.yvalue_ << ")");
                }
            };

            // ElliptCurv_cus_class implementation

            typedef ElliptCurv_cus_class<P> this_t;
            typedef class ElliptCurv_cus_class<P>::Point point_t;

            // ctor
            // Initialize EC as y^2 = x^3 + ax + b
            ElliptCurv_cus_class(long long int a, long long int b)
                : a_(a),
                    b_(b),
                    m_table_(),
                    table_filled_(false)
            {                    
            }

            // Calculating the points (group elements) for this EC

            void CalculatePoints()
            {
                long long int xvalue_val[P];
                long long int yvalue_val[P];
                for ( long long int n = 0; n < P; ++n )
                {
                    long long int nsq = n*n;
                    xvalue_val[n] = ((n*nsq) + a_.i() * n + b_.i()) % P;
                    yvalue_val[n] = nsq % P;                        
                }

                for ( long long int n = 0; n < P; ++n )
                {
                    for ( long long int m = 0; m < P; ++m )
                    {
                        if ( xvalue_val[n] == yvalue_val[m] )
                        {
                            // Points of m,n
                            m_table_.push_back(Point(n,m,*this));
                        }
                    }
                }
                table_filled_ = true;
            }
            // get a point (group element) on the curve 
            Point operator[](long long int n)
            {
                if ( !table_filled_ )
                {
                    // call Calculate points
                    CalculatePoints();
                }

                return m_table_[n];
            }
            // number of elements in this group
            size_t Size() const { return m_table_.size(); }
            // the degree P of this EC
            long long int Degree() const { return P; }
            // the parameter a (as an element of Fp)
            GaloisFiniteField<P> a() const { return a_; }
            // the paramter b (as an element of Fp)
            GaloisFiniteField<P> b() const { return b_; }

            // ostream handler: print this curve in human readable form
            template <long long int T>
            friend ostream& operator <<(ostream& os, const ElliptCurv_cus_class<T>& ElliptCurv_cus_class);
            // print all the elements of the EC group
            ostream& PrintTable(ostream &os, long long int columns=4);

            private:
                typedef std::vector<Point>  m_table_t;

                // table of points
                m_table_t                   m_table_;
                // paramter a of the EC equation
                GaloisFiniteField<P>       a_;
                // parameter b of the EC equation
                GaloisFiniteField<P>       b_;
                // true if the table has been calculated
                bool table_filled_;
    };

    template<long long int T>
        typename ElliptCurv_cus_class<T>::Point ElliptCurv_cus_class<T>::Point::ONE(0,0);
                            
    template<long long int T>
    ostream& operator <<(ostream& os, const ElliptCurv_cus_class<T>& ElliptCurv_cus_class)
    {
        os << "y^2 mod " << T << " = (x^3" << showpos;
        if ( ElliptCurv_cus_class.a_ != 0 )
        {
            os << ElliptCurv_cus_class.a_ << "x";
        }

        if ( ElliptCurv_cus_class.b_.i() != 0 )
        {
            os << ElliptCurv_cus_class.b_; 
        }

        os << noshowpos << ") mod " << T;
        return os;
    }
    
    template<long long int P>
    ostream& ElliptCurv_cus_class<P>::PrintTable(ostream &os, long long int columns)
    {
        if ( table_filled_ )
        {
            long long int col = 0;
            typename ElliptCurv_cus_class<P>::m_table_t::iterator iter = m_table_.begin();
            for ( ; iter!=m_table_.end(); ++iter )
            {
                os << "(" << (*iter).xvalue_.i() << ", " << (*iter).yvalue_.i() << ") ";
                if ( ++col > columns )
                {
                    os << "\n";
                    col = 0;
                }
            }
        }
        else
        {
            os << "ElliptCurv_cus_class, F_" << P;
        }
        return os;
        }                        
}

// utils



using namespace EllipCurv;
using namespace utils;

// Driver Code

int main(int argc, char *argv[])
{
    // Using the Elliptic Curve typedef
    typedef ElliptCurv_cus_class<263> t_value;

    long long int inp1, inp2;

    // Getting a and b values from the user
    cout<< "Please enter a value : ";
    cin>> inp1;
    cout<< "Please enter b value : ";
    cin>> inp2;

    t_value myElliptCurv_cus_class(inp1,inp2);
    
    cout<< "The elliptic curve: " << myElliptCurv_cus_class << "\n\n";

    // If the period is very large this is big and slow
    myElliptCurv_cus_class.CalculatePoints();

    //cout<< "\nGroup elements co-ordinates :\n";

    //	cout<<endl<<"Generated Points : \n"<<endl;
    //myElliptCurv_cus_class.PrintTable(cout,5);

    cout<< "\n\n===================================================\n\n";

    t_value::Point P = myElliptCurv_cus_class[2];
    t_value::Point Q = myElliptCurv_cus_class[3];

    cout<< "P \t: " << P << "\n";
    cout<< "Q \t: " << Q << "\n";
    t_value::Point R = P;
    R += Q;
    R = P;
    R += R;

    cout<< "R \t: " << R << "\n";

    t_value::Point G = myElliptCurv_cus_class[0];


    while( (G.y() == 0 || G.x() == 0) || (G.Order()<2) )
    {
        // calculating G
        long long int n = (long long int)(frand()*myElliptCurv_cus_class.Size());
        G = myElliptCurv_cus_class[n];

    }
    

    cout<< "G \t: " << G << endl;
    cout<< "order of G : " << G.Order() << "\n";
    
    // Sender
    long long int a = irand(1,myElliptCurv_cus_class.Degree()-1);


    // public key : a * G
    t_value::Point Pa = a*G; 

    cout << "Alice' public key Pa = " << a << "*" << G << " = " << Pa << endl;    
        

    // Reciever's Public key = b * G

    long long int b = irand(1,myElliptCurv_cus_class.Degree()-1);;

    // public key :
    t_value::Point Pb = b*G;      
    cout<< "Bob's public key = " << Pb << endl;    
    
    cout<< "\n===================================================\n\n"; 

    long long int j = irand(1,myElliptCurv_cus_class.Degree()-1);;

    t_value::Point Pj = j*G;
    cout << "Eve's public key Pj = " << j << "*" << G << " = " << Pj << endl;    



    long long int message_x,message_y;
    
    // Getting the message points :

    cout<< "Please enter the message points: \n";
    cout<< "\nmessage_x co-ordinate : ";
    cin>> message_x;
    cout<< "message_y co-ordinate : ";
    cin>> message_y;

    cout<< "\n";

    cout<< "*************************************************\n";
    cout<< "* Alice's input message points : ("<< message_x << ", "<< message_y << ")\n";
    cout<< "*************************************************\n\n";

    // Encryption :
    t_value::Point Pk = a*Pb;

    // cipher message:
    t_value::finite_field cipher_x(message_x*Pk.x());
    t_value::finite_field cipher_y(message_y*Pk.y());
    
    // encrypted message is: Pa,cipher_x,cipher_y
    cout<< "Encrypted message points using diffie hellman : \n" ;
    cout<< "\t "<< "(cipher_x,cipher_y) = ( " << cipher_x << ", " << cipher_y <<" )\n\n";
    
    // Decryption :
    Pk = b*Pa;
    t_value::finite_field message_xd = cipher_x/Pk.x();
    t_value::finite_field message_yd = cipher_y/Pk.y();

    cout<< "\n************************************************************";
    cout<< "\n* Bob's Decrypted message points = (" << message_xd << ", " << message_yd <<")   " ;
    cout<< "\n************************************************************\n\n";

    Pk = j*Pa;
    message_xd = cipher_x/Pk.x();
    message_yd = cipher_y/Pk.y();

    cout << "\nEve's decrypted message from Alice = (" << message_xd << ", " << message_yd << ")" << endl;


    //cout<< "\n================================================================================\n"; 
    cout<< "--------Eve cannot manipulate the message inbetween as Eve gets wrong message--------";
    //cout<< "\n================================================================================\n"; 
    cout<< endl;
    
    system("PAUSE");

    return EXIT_SUCCESS;
}
