#include "Lagrangian.h"


int main(int argc, char const ** argv){

	if(argc > 1){
		std::string loglevel = argv[1];
		Diagnositics::Log::ReportingLevel() = Diagnositics::Log::FromString(loglevel);
	}
	else{
		Diagnositics::Log::ReportingLevel() = Diagnositics::logINFO;

	}
  //
	// Lagrangian::SpecialUnitary f(3);
  //
  //
	// auto w = f.group->get_fweight();
	// std::cout<<w.size()<<std::endl;
  //
  //
	 Representation::LieBase<Representation::GroupType::A> A(3);
	 //std::cout<<A.adjoint_rep().omega.transpose()<<std::endl;


  return 0;
}
