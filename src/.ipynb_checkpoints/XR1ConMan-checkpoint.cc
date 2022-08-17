#include "QGSP_BIC.hh"

#include "XR1ConMan.hh"

//////////////////////////////////////////////////
//   Constructors and destructor                //
//////////////////////////////////////////////////
XR1ConMan::XR1ConMan()
{
	Init();
}


XR1ConMan::XR1ConMan(const G4String fileName)
{
	Init(fileName);
}


XR1ConMan::~XR1ConMan()
{
}


//////////////////////////////////////////////////
//   Initialization function                    //
//////////////////////////////////////////////////
void XR1ConMan::Init(const G4String fileName)
{

	if ( !fileName ) SetDefault();
	else if ( !Load(fileName) ) SetDefault();
    
    // initialize detector maps
    if (m_GeomID == 0) SetPatiMap0(m_PatDVX, m_PatDVY, m_PatDVZ);
    else               SetPatiMap1(m_NumOfS);
    
    PrintConfiguration();
}

void XR1ConMan::SetDefault()
{
	// set default values to config features
	// Computing resource
	m_UseMTD		= true;
	m_NofTRD		= 7;

	// physics list
	m_PhyList = new QGSP_BIC;

	//reaction area
	m_InterXL		= 500.0 *  mm;
	m_InterYL		= 500.0 *  mm;
    m_InterZL		= 500.0 *  mm;
	m_SLabMat		= "G4_AIR";

	// Beam 
	m_BeamKE		= 230.0 * MeV;
	m_BeamOR		= 3.0	*  mm;
	m_SParName	        = "proton";

    // choice of geometry
    m_GeomID        = 0;
    
	// patient 
	m_ColltoPat	        = 200.0 *  mm;
	m_PatiXL		= 50.0 *  mm;
    m_PatiYL		= 50.0 *  mm;
    m_PatiZL		= 50.0 *  mm;
	m_PatDVX		= 100;
    m_PatDVY		= 100;
    m_PatDVZ		= 100;
    m_PatiQX        = 1.0;
    m_PatiQY        = 1.0;
    m_PatiQZ        = 1.0;
    m_PatiBX        = 1.0  *  mm;
    m_PatiBY        = 1.0  *  mm;
    m_PatiBZ        = 1.0  *  mm;
    m_SPatiMat	        = "G4_WATER";
    
    // patient 2
    m_NumOfS        = 4;
    m_radInS        = 0.03 * mm;
    m_patSpQ        = 2.0;
    
        // detector map
	m_PM  = new XR1PatMap(m_PatDVX, m_PatDVY, m_PatDVZ);
}


//////////////////////////////////////////////////
//   Load configuration file                    //
//////////////////////////////////////////////////
bool XR1ConMan::Load(const G4String fileName)
{
	// Open file
	std::ifstream file(fileName, std::ifstream::in);
	if ( !file.is_open() ) return false;

	// Read line by line
	std::string line;
	char hfile[1000];
	while ( std::getline(file, line) )
	{
		if ( StartsWith(line, "#") ) continue;

		// Read configurations: Computing
		if (StartsWith(line, "USEMULTITHREADS")){
			sscanf(line.data(), "USEMULTITHREADS %s", hfile);
			if      ( hfile == "ON"  ) SetUseMTD(true);
			else if ( hfile == "OFF" ) SetUseMTD(false);
            
		}else if (StartsWith(line, "NTHREADS")){
			sscanf(line.data(), "NTHREADS %s", hfile);
			SetNofTRD(std::stoi(hfile));
		
        // physics list 
		}else if (StartsWith(line, "USEHTPHYSICS")){
			sscanf(line.data(), "USEHTPHYSICS %s", hfile);
			if      ( hfile == "ON"  ) SetHTPhys(new XR1PhyList());
			else if ( hfile == "OFF" ) SetHTPhys(new QGSP_BIC);
		
        // lab parameters 
		}else if (StartsWith(line, "WORLDX")){
			sscanf(line.data(), "WORLDX %s", hfile);
            SetInteXL(std::stod(hfile));
		
		}else if (StartsWith(line, "WORLDY")){
			sscanf(line.data(), "WORLDY %s", hfile);
			SetInteYL(std::stod(hfile));
		
        }else if (StartsWith(line, "WORLDZ")){
			sscanf(line.data(), "WORLDZ %s", hfile);
			SetInteZL(std::stod(hfile));
            
		}else if (StartsWith(line, "LABMATERIAL")){
			sscanf(line.data(), "LABMATERIAL %s", hfile);
			SetLabMat(hfile);
		
        // beam 
		}else if (StartsWith(line, "BEAMKINETICENERGY")){
			sscanf(line.data(), "BEAMKINETICENERGY %s", hfile);
			SetBeamKE(std::stod(hfile));
		
		}else if (StartsWith(line, "BEAMRADIUS")){
			sscanf(line.data(), "BEAMRADIUS %s", hfile);
			SetBeamOR(std::stod(hfile));
		
		}else if (StartsWith(line, "PARTICLENAME")){
			sscanf(line.data(), "PARTICLENAME %s", hfile);
			SetParName(hfile);
            
		// choice of geometry
        }else if (StartsWith(line, "WHICHGEOMETRY")){
			sscanf(line.data(), "WHICHGEOMETRY %s", hfile);
			SetGeomID(std::stoi(hfile));
            
        // patient
		}else if (StartsWith(line, "CENTRETOPATIENT")){
			sscanf(line.data(), "CENTRETOPATIENT %s", hfile);
			SetCollToPat(std::stod(hfile));
		
        }else if (StartsWith(line, "PATIENTXLEN")){
			sscanf(line.data(), "PATIENTXLEN %s", hfile);
			SetPatiXL(std::stod(hfile));
            
        }else if (StartsWith(line, "PATIENTYLEN")){
			sscanf(line.data(), "PATIENTYLEN %s", hfile);
			SetPatiYL(std::stod(hfile));
            
		}else if (StartsWith(line, "PATIENTZLEN")){
			sscanf(line.data(), "PATIENTZLEN %s", hfile);
			SetPatiZL(std::stod(hfile));
		
		}else if (StartsWith(line, "DEVIDEPATGEOMX")){
			sscanf(line.data(), "DEVIDEPATGEOMX %s", hfile);
			SetPatDVX(std::stoi(hfile));
            
        }else if (StartsWith(line, "DEVIDEPATGEOMY")){
			sscanf(line.data(), "DEVIDEPATGEOMY %s", hfile);
			SetPatDVY(std::stoi(hfile));
            
        }else if (StartsWith(line, "DEVIDEPATGEOMZ")){
			sscanf(line.data(), "DEVIDEPATGEOMZ %s", hfile);
			SetPatDVZ(std::stoi(hfile));
		
		}else if (StartsWith(line, "PATIENTMAT")){
			sscanf(line.data(), "PATIENTMAT %s", hfile);
			SetPatiMat(hfile);
            
        }else if (StartsWith(line, "QGEOMPROX")){
			sscanf(line.data(), "QGEOMPROX %s", hfile);
			SetPatiQX(std::stod(hfile));
            
		}else if (StartsWith(line, "QGEOMPROY")){
			sscanf(line.data(), "QGEOMPROY %s", hfile);
			SetPatiQY(std::stod(hfile));
            
		}else if (StartsWith(line, "QGEOMPROZ")){
			sscanf(line.data(), "QGEOMPROZ %s", hfile);
			SetPatiQZ(std::stod(hfile));
            
		}else if (StartsWith(line, "B1GEOMPROX")){
			sscanf(line.data(), "B1GEOMPROX %s", hfile);
			SetPatiBX(std::stod(hfile));
            
		}else if (StartsWith(line, "B1GEOMPROY")){
			sscanf(line.data(), "B1GEOMPROY %s", hfile);
			SetPatiBY(std::stod(hfile));
            
		}else if (StartsWith(line, "B1GEOMPROZ")){
			sscanf(line.data(), "B1GEOMPROZ %s", hfile);
			SetPatiBZ(std::stod(hfile));
           
        // patient 2
		}else if (StartsWith(line, "NUMBOFSPHERE")){
			sscanf(line.data(), "NUMBOFSPHERE %s", hfile);
			SetNumOfS(std::stoi(hfile));
		
		}else if (StartsWith(line, "RADIUSOFINNERSPHERE")){
			sscanf(line.data(), "RADIUSOFINNERSPHERE %s", hfile);
			SetRadInS(std::stod(hfile));
            
		}else if (StartsWith(line, "QGEOMPROFORRADIUS")){
			sscanf(line.data(), "QGEOMPROFORRADIUS %s", hfile);
			SetPatSpQ(std::stod(hfile));
            
		}
	}

	return true;
}

//////////////////////////////////////////////////
//   Print Configuration ...                    //
//////////////////////////////////////////////////
void XR1ConMan::PrintConfiguration()
{
    // Computing
    std::cout << "*********************Configuration*********************"<< std::endl;
    std::cout << "XR1::Load() => USEMULTITHREADS         " << m_UseMTD    << std::endl;
    std::cout << "XR1::Load() => NTHREADS                " << m_NofTRD    << std::endl;
    std::cout << "XR1::Load() => WORLDX                  " << m_InterXL   << std::endl;
    std::cout << "XR1::Load() => WORLDX                  " << m_InterYL   << std::endl;
    std::cout << "XR1::Load() => WORLDX                  " << m_InterZL   << std::endl;
    std::cout << "XR1::Load() => BEAMKINETICENERGY       " << m_BeamKE    << std::endl;
    std::cout << "XR1::Load() => BEAMRADIUS              " << m_BeamOR    << std::endl;
    std::cout << "XR1::Load() => PARTICLENAME            " << m_SParName  << std::endl;
    std::cout << "XR1::Load() => WHICHGEOMETRY           " << m_GeomID    << std::endl;
    std::cout << "XR1::Load() => CENTRETOPATIENT         " << m_ColltoPat << std::endl;
    std::cout << "XR1::Load() => PATIENTXLEN             " << m_PatiXL    << std::endl;
    std::cout << "XR1::Load() => PATIENTYLEN             " << m_PatiYL    << std::endl;
    std::cout << "XR1::Load() => PATIENTZLEN             " << m_PatiZL    << std::endl;
    std::cout << "XR1::Load() => DEVIDEPATGEOMX          " << m_PatDVX    << std::endl;
    std::cout << "XR1::Load() => DEVIDEPATGEOMY          " << m_PatDVY    << std::endl;
    std::cout << "XR1::Load() => DEVIDEPATGEOMZ          " << m_PatDVZ    << std::endl;
    std::cout << "XR1::Load() => QGEOMPROX               " << m_PatiQX    << std::endl;
    std::cout << "XR1::Load() => QGEOMPROY               " << m_PatiQY    << std::endl;
    std::cout << "XR1::Load() => QGEOMPROZ               " << m_PatiQZ    << std::endl;
    std::cout << "XR1::Load() => B1GEOMPROX              " << m_PatiBX    << std::endl;
    std::cout << "XR1::Load() => B1GEOMPROY              " << m_PatiBY    << std::endl;
    std::cout << "XR1::Load() => B1GEOMPROZ              " << m_PatiBZ    << std::endl;
    std::cout << "XR1::Load() => NUMBOFSPHERE            " << m_NumOfS    << std::endl;
    std::cout << "XR1::Load() => RADIUSOFINNERSPHERE     " << m_radInS    << std::endl;
    std::cout << "XR1::Load() => QGEOMPROFORRADIUS       " << m_patSpQ    << std::endl;
    std::cout << "XR1::Load() => PATIENTMAT              " << m_SPatiMat  << std::endl;
    std::cout << "******************EndOfConfiguration*******************"<< std::endl;
}

//////////////////////////////////////////////////
//   Test whether a line starts with ...        //
//////////////////////////////////////////////////
bool XR1ConMan::StartsWith(const std::string& text, const std::string& token)
{
	if ( text.length() < token.length() ) return false;
	return ( text.compare(0, token.length(), token) == 0 );
}
