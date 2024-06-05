#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int precision;
class TaylorExpansion{
	public:	
		static double arctan(double angle){
			int sgn=-1;
			double res=angle;
			double new_element=angle;
			for(int i=3;new_element>0 && i<=precision*2;i+=2){
				new_element=new_element*angle*angle*(i-2)/i;
				res+=new_element*sgn;
				sgn*=-1;
			}
			return res;
		}
		static double sin(double angle){
			int sgn=-1;
			double res=angle;
			double new_element=angle;
			for(int i=2;new_element>0 && i<=precision*2;i+=2){
				new_element=new_element*angle*angle/(i*(i+1));
				res+=new_element*sgn;
				sgn*=-1;
			}
			return res;
		}
		static double cos(double angle){
			int sgn=-1;
			double res=1;
			double new_element=1;
			for(int i=2;new_element>0 && i<=precision*2;i+=2){
				new_element=new_element*angle*angle/(i*(i-1));
				res+=new_element*sgn;
				sgn*=-1;
			}
			return res;

		}
		static double tan(double angle){
			return sin(angle)/cos(angle);
		}
};
class CORDIC{
	public:
		static constexpr double CORDIC_CONSTANT=0.607252935009;
		static double sin(double angle){
			double x=CORDIC_CONSTANT,y=0;
			double xp,yp;
			double partialAngle;
			double pow2=1;
			int orientation=1;
			for(int i=0;i<=precision;i++){
				orientation=partialAngle/abs(partialAngle);
				
				xp=x-pow2*y*orientation;
				yp=pow2*orientation*x+y;
				partialAngle=partialAngle-(orientation*TaylorExpansion::arctan(pow2));

				pow2/=2;
				x=xp;y=yp;
			}
			return xp;
		}
		static double cos(double angle){
			double x=CORDIC_CONSTANT,y=0;
			double xp,yp;
			double partialAngle;
			double pow2=1;
			int orientation=1;
			for(int i=0;i<=precision;i++){
				orientation=partialAngle/abs(partialAngle);
				
				xp=x-pow2*y*orientation;
				yp=pow2*orientation*x+y;
				partialAngle=partialAngle-(orientation*TaylorExpansion::arctan(pow2));

				pow2/=2;
				x=xp;y=yp;
			}
			return yp;
		}
};
void Error(){
	double ex=(double)(rand())/rand();
	cout<<"SINE ERROR:\n";
	cout<<"TAYLOR EXPANSION: "<<abs(sin(ex)-TaylorExpansion::sin(ex))<<'\n';
	cout<<"CORDIC ALGORITHM: "<<abs(sin(ex)-CORDIC::sin(ex))<<"\n\n\n";
	cout<<"COSINE ERROR:\n";
	cout<<"TAYLOR EXPANSION: "<<abs(cos(ex)-TaylorExpansion::cos(ex))<<'\n';
	cout<<"CORDIC ALGORITHM: "<<abs(cos(ex)-CORDIC::cos(ex))<<"\n\n\n";
}
int main(){
	srand(time(0));
	cout<<fixed<<setprecision(10);
	precision=10000000;
	Error();

}
