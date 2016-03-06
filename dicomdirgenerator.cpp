#include <dicomdirgenerator>

DICOMDIRGenerator::DICOMDIRGenerator()
{
//    string dir = "/media/WDC/ADC_4.3/1.2.528.1.1001.200.10.1485.3833.784206140.20160303093653992/SDY00000";
//    string outfile = "dcmdir";
// gdcm::Trace::DebugOn();
// gdcm::Trace::SetStreamToFile("log");

//    gdcm::Directory d;
//    d.Load(dir.c_str(),true);
//    int nfiles = d.Load(dir, true);
//    if (nfiles == 0 ) return 1;

//    string descriptor = "My_Descriptor";

//    gdcm::Directory::FilenamesType filenames = d.GetFilenames();

//    gdcm::DICOMDIRGenerator gen;
//    gen.SetFilenames( filenames );
//    gen.SetDescriptor( descriptor.c_str() );
//    if( !gen.Generate() )
//      {
//        qDebug()<<"error";
//      return 1;
//      }

//    gdcm::FileMetaInformation met;
//    met.SetSourceApplicationEntityTitle( "GenerateDICOMDIR" );
//    gdcm::Writer writer;
//    writer.SetFile( gen.GetFile() );
//    writer.SetFileName( outfile.c_str() );
//    if( !writer.Write() )
//      {
//      return 1;
    //      }
}

DICOMDIRGenerator::~DICOMDIRGenerator()
{

}
