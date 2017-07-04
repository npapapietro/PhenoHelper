#include "Lagrangian.h"

namespace Lagrangian_Form {
	using namespace Representation;

	Fermion::Fermion(std::string name, double mass) {
		this->name = name;
		this->mass = mass;
	};

	Scalar::Scalar(std::string name, double mass)
	{
		this->name = name;
		this->mass = mass;
	};

	GBoson::GBoson(std::string name)
	{
		this->name = name;
	}

	YangMills_Groups::YangMills_Groups(std::string type, int N)
	{
		if(type=="SU")
		{
			TeXName = str(boost::format("SU(%1)") %N);
			group = std::shared_ptr<GroupBase>(new LieBase<GroupType::A>(N - 1));
			FILE_LOG(Diagnositics::logDEBUG3) << TeXName + "called";
		}
		else if(type=="SO")
		{
			TeXName = str(boost::format("SO(%1)") %N);
			if(N%2==0)
			{
				group = std::shared_ptr<GroupBase>(new LieBase<GroupType::D>(N / 2));
			}
			else
			{
				group = std::shared_ptr<GroupBase>(new LieBase<GroupType::B>((N - 1) / 2));
			}
			FILE_LOG(Diagnositics::logDEBUG3) << TeXName + "called";
		}
		else if(type == "Sp")
		{
			TeXName = str(boost::format("Sp(%1)") %N);
			group = std::shared_ptr<GroupBase>(new LieBase<GroupType::C>(N));
			FILE_LOG(Diagnositics::logDEBUG3) << TeXName + "called";
		}
		else if(type == "U")
		{
			TeXName = "U(1)";
			//group = std::unique_ptr<GroupBase>( new CircleGroup() );
			FILE_LOG(Diagnositics::logDEBUG3) << TeXName + "called";
		}
	}

	YangMills_Groups::~YangMills_Groups()
	{
	}

/*
* Lagrangian Class
*/

std::vector<std::shared_ptr<YangMills_Groups>> Lagrangian::get_Gauge_Groups() const
{
	return Gauge_Groups;
}
std::vector<std::shared_ptr<ParticleTraits>> Lagrangian::get_Particle_Contents() const
{
	return Particle_Contents;
}

/*
* KineticEnergyTerm Class
*/

	KineticEnergyTerm::KineticEnergyTerm(ParticleTraits *pcle, Lagrangian L)
	{
		particle = std::shared_ptr<ParticleTraits>(pcle);
		this->TeXName = "\\partial_\\mu ";
		Gauge_Int(L);
	}



	void KineticEnergyTerm::Gauge_Int(Lagrangian L)
	{
	//Iterate through the group content of particle and classify
		for (size_t i = 0; i < particle->charges.size(); i++)
		{
			Representation::weight current_rep = *(particle->charges[i]);

			if(current_rep ==  L.Gauge_Groups[i]->group->get_adjoint_rep())
			{
					this->TeXName+=Term_To_String(1,L.Gauge_Groups[i]->TeXName);
			}
			else if (L.Gauge_Groups[i]->group->is_singlet(current_rep)){
					this->TeXName+=Term_To_String(0,L.Gauge_Groups[i]->TeXName);
			}
			else if (L.Gauge_Groups[i]->group->get_Rank()==0){
					std::string ss;
					ss = str( boost::format( "\\frac{%1}{%2}") %current_rep.omega(0).numerator() %current_rep.omega(0).numerator() );
					this->TeXName+=Term_To_String(3,L.Gauge_Groups[i]->TeXName,ss);
			}
			else
				this->TeXName+=Term_To_String(4,L.Gauge_Groups[i]->TeXName);

		}
	}

	std::string KineticEnergyTerm::Term_To_String(int classifier, std::string _TeXName_, std::string U1charge)
	{
		/*
		* 0 = singlet
		* 1 = adjoint
		* 2 = fundamental rep
		* 3 = U(1)
		*/

		switch (classifier)
		{
			case 0:
			{
				return "";
			}
			case 1:
			{
				return str(boost::format("-i g_{%1} [\\vec{W}^{%1}_\\mu, \\cdot]") %_TeXName_);
			}
			case 2:
			{
				return str(boost::format("-i g_{%1} \\vec{W}^{%1}_\\mu") %_TeXName_);
			}
			case 3:
			{
				return str(boost::format("-i g_{%1} %2 W^{%1}_\\mu") %_TeXName_ %U1charge);
			}
			default:
				return "";
		}
	}
}
