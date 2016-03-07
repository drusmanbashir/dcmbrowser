#include<dcmdump.h>
#include <sstream>
#include <string>
#include <qdebug.h>
#include <QString>
using namespace std;


typedef std::set<gdcm::DataElement> DataElementSet;
typedef DataElementSet::const_iterator ConstIterator;

DCMDump::DCMDump(const QString &dcmFile)
{
    string tmpname;
    tmpname = dcmFile.toStdString();
    gdcm::Reader reader;
    reader.SetFileName(tmpname.c_str());
    if( !reader.Read() )
      {
      qDebug() << "Could not read: " << dcmFile;

      }
    std::stringstream strm;

    file = reader.GetFile();
    ds = file.GetDataSet();
    fmi = file.GetHeader();

    ms.SetFromFile(file);


     parse();



}

void DCMDump::parse()
{
    qDebug()<<"Parsing file now.. ";


     if( ms != gdcm::MediaStorage::MediaStorageDirectoryStorage )
       {
       qDebug() << "This file is not a DICOMDIR" ;

       }

     if (fmi.FindDataElement( gdcm::Tag (0x0002, 0x0002)))
       {   strm.str("");
       fmi.GetDataElement( gdcm::Tag (0x0002, 0x0002) ).GetValue().Print(strm);
       }
     else
       {
       qDebug() << " Media Storage Sop Class UID not present";
       }

     if ("1.2.840.10008.1.3.10"!=strm.str())
       {
       qDebug() << "This file is not a DICOMDIR" ;

       }

       ConstIterator it = ds.GetDES().begin();
       for( ; it != ds.GetDES().end(); ++it)
         {

         if (it->GetTag()==gdcm::Tag (0x0004, 0x1220))
           {

           const gdcm::DataElement &de = (*it);
           // ne pas utiliser GetSequenceOfItems pour extraire les items
           gdcm::SmartPointer<gdcm::SequenceOfItems> sqi =de.GetValueAsSQ();
           unsigned int itemused = 1;
           while (itemused<=sqi->GetNumberOfItems())

             {
             strm.str("");

             if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1430)))
               sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1430)).GetValue().Print(strm);

             //TODO il faut trimer strm.str() avant la comparaison
             while((strm.str()=="PATIENT")||((strm.str()=="PATIENT ")))
               {
                 QString tmp = QString::fromStdString(strm.str());

               qDebug() << tmp ;
               strm.str("");
               if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0010, 0x0010)))
                 sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0010, 0x0010)).GetValue().Print(strm);
               tmp = QString::fromStdString(strm.str());
               qDebug() << "PATIENT NAME : " << tmp ;


               //PATIENT ID
               strm.str("");
               if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0010, 0x0020)))
                 sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0010, 0x0020)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
               qDebug() << "PATIENT ID : " << tmp ;
ptID=tmp;
               /*ADD TAG TO READ HERE*/
               qDebug() << "=========================== "  ;
               itemused++;
               strm.str("");
               if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1430)))
                 sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1430)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());

               //TODO il faut trimer strm.str() avant la comparaison
               while((strm.str()=="STUDY")||((strm.str()=="STUDY ")))
                 {
                 qDebug() << "  " << tmp ;
                 //UID
                 strm.str("");
                 if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0020, 0x000d)))
                   sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0020, 0x000d)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
                 qDebug() << "      STUDY UID : " << tmp ;

                 //STUDY DATE
                 strm.str("");
                 if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0008, 0x0020)))
                   sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0008, 0x0020)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
                 qDebug() << "      STUDY DATE : " << tmp ;
 studyDate=tmp;
                 //STUDY DESCRIPTION
                 strm.str("");
                 if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0008, 0x1030)))
                   sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0008, 0x1030)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
                 qDebug() << "      STUDY DESCRIPTION : " << tmp ;

                 /*ADD TAG TO READ HERE*/
                 qDebug() << "      " << "=========================== "  ;

                 itemused++;
                 strm.str("");
                 if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1430)))
                   sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1430)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());

                 //TODO il faut trimer strm.str() avant la comparaison
                 while((strm.str()=="SERIES")||((strm.str()=="SERIES ")))
                   {
                   qDebug() << "      " << tmp ;
                   strm.str("");
                   if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0020, 0x000e)))
                     sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0020, 0x000e)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
                   qDebug() << "          SERIE UID" << tmp ;

                   //SERIE MODALITY
                   strm.str("");
                   if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0008, 0x0060)))
                     sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0008, 0x0060)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
                   qDebug() << "          SERIE MODALITY" << tmp ;
modality=tmp;
                   //SERIE DESCRIPTION
//                                   next three lines throw sigabort on certain DICOMDIR files
//                   strm.str("");
//                   if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0008, 0x103e)))
//                     sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0008, 0x103e)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
//                   qDebug() << "          SERIE DESCRIPTION" << tmp ;


                   /*ADD TAG TO READ HERE*/

                   qDebug() << "          " << "=========================== "  ;
                   itemused++;
                   strm.str("");



                   if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1430)))
                     sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1430)).GetValue().Print(strm);
                   tmp = QString::fromStdString(strm.str());


                   //TODO il faut trimer strm.str() avant la comparaison
                   while ((strm.str()=="IMAGE")||((strm.str()=="IMAGE ")))
                     // if(tmp=="IMAGE")
                     {
                  //   qDebug() << "          " << tmp ;


                     //UID
                     strm.str("");
                     if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1511)))
                       sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1511)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
                //     qDebug() << "              IMAGE UID : " << tmp ;

                     //PATH de l'image
                     strm.str("");
                     if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1500)))
                       sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1500)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());
                //     qDebug() << "              IMAGE PATH : " << tmp ;
                     /*ADD TAG TO READ HERE*/



                     if(itemused < sqi->GetNumberOfItems())
                       {itemused++;
                       }else{break;}

                     strm.str("");

                     if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1430)))
                       sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1430)).GetValue().Print(strm); tmp = QString::fromStdString(strm.str());

                     }
                   }
                 }
               }
             itemused++;
             }
           }
         }


}

void DCMDump::anonymize()
{

}

QString DCMDump::outputPtID()
{
 return(ptID);
}

QString DCMDump::outputModality()
{
 return(modality);
}

QString DCMDump::outputStudydate()
{
    return(studyDate);

}
