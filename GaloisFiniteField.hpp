

namespace EllipCurv
{
    namespace detail
    {            
        //g = a*u + b*v
        long long int EGCD(long long int a, long long int b, long long int& u, long long int &v)
        { 
            u = 1; 
            v = 0; 
            long long int g = a; 
            long long int u1 = 0;
            long long int v1 = 1; 
            long long int g1 = b; 
            while (g1 != 0) 
            { 
                long long int q = g/g1;
                long long int t1 = u - q*u1; 
                long long int t2 = v - q*v1; 
                long long int t3 = g - q*g1; 
                u = u1; v = v1; g = g1; 
                u1 = t1; v1 = t2; g1 = t3; 
            } 
            
            return g;
        }
        
        //  x * z == 1 (mod n) for z 
        long long int InvMod(long long int x, long long int n)
        { 
            x = x % n;  
            long long int u,v,g,z;
            g = EGCD(x, n, u,v);
            if (g != 1) 
            { 
                z = 0; 
            } 
            else 
            { 
                z = u % n;
            } 
            return z;
        }
    }
    
    template<long long int P>
    class   GaloisFiniteField
    {
        long long int     i_;
        
        void    assign(long long int i)
        {
            i_ = i;
            if ( i<0 )
            {                    
                // the (i%P) term is to ensure that i is in the correct range before normalizing
                i_ = (i%P) + 2*P;
            }

            i_ %= P;
        }
        
        public:
            GaloisFiniteField()
                : i_(0)
            {}

            explicit GaloisFiniteField(long long int i)
            {
                assign(i);
            }

            GaloisFiniteField(const GaloisFiniteField<P>& righthandside) 
                : i_(righthandside.i_)               
            {
            }

            long long int i() const { return i_; }                

            GaloisFiniteField operator-() const
            {
                return GaloisFiniteField(-i_);
            }                                

            GaloisFiniteField& operator=(long long int i)
            {
                assign(i);
                return *this;
            }

            GaloisFiniteField<P>& operator=(const GaloisFiniteField<P>& righthandside)
            {
                i_ = righthandside.i_;
                return *this;
            }

            GaloisFiniteField<P>& operator*=(const GaloisFiniteField<P>& righthandside)
            {
                i_ = (i_*righthandside.i_) % P;
                return *this;           
            }

            friend bool operator==(const GaloisFiniteField<P>& lhs, const GaloisFiniteField<P>& righthandside)
            {
                return (lhs.i_ == righthandside.i_);
            }

            friend bool operator==(const GaloisFiniteField<P>& lhs, long long int righthandside)
            {
                return (lhs.i_ == righthandside);
            }

            friend bool operator!=(const GaloisFiniteField<P>& lhs, long long int righthandside)
            {
                return (lhs.i_ != righthandside);
            }                

            friend GaloisFiniteField<P> operator/(const GaloisFiniteField<P>& lhs, const GaloisFiniteField<P>& righthandside)
            {
                return GaloisFiniteField<P>( lhs.i_ * detail::InvMod(righthandside.i_,P));
            }

            friend GaloisFiniteField<P> operator+(const GaloisFiniteField<P>& lhs, const GaloisFiniteField<P>& righthandside)
            {
                return GaloisFiniteField<P>( lhs.i_ + righthandside.i_);
            }

            friend GaloisFiniteField<P> operator-(const GaloisFiniteField<P>& lhs, const GaloisFiniteField<P>& righthandside)
            {
                return GaloisFiniteField<P>( lhs.i_ - righthandside.i_);
            }
            // a + long long int
            friend GaloisFiniteField<P> operator+(const GaloisFiniteField<P>& lhs, long long int i)
            {
                return GaloisFiniteField<P>( lhs.i_+i);
            }

            friend GaloisFiniteField<P> operator+(long long int i, const GaloisFiniteField<P>& righthandside)
            {
                return GaloisFiniteField<P>( righthandside.i_+i);
            }

            friend GaloisFiniteField<P> operator*(long long int n, const GaloisFiniteField<P>& righthandside)
            {
                return GaloisFiniteField<P>( n*righthandside.i_);
            }                

            friend GaloisFiniteField<P> operator*(const GaloisFiniteField<P>& lhs, const GaloisFiniteField<P>& righthandside)
            {
                return GaloisFiniteField<P>( lhs.i_ * righthandside.i_);
            }

            template<long long int T>
            friend ostream& operator<<(ostream& os, const GaloisFiniteField<T>& g)
            {
                return os << g.i_;
            }
    };
}

