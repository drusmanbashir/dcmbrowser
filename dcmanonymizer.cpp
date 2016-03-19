#include <gdcmWriter.h>

#include <dcmanonymizer.h>
#include <QDebug>
#include <string>



typedef std::set<gdcm::DataElement> DataElementSet;
typedef DataElementSet::const_iterator ConstIterator;


DCMAnonymizer::DCMAnonymizer(const QString &fileNm): fileName(fileNm), ptNameTag(0x10,0x10)
{
    gdcm::Reader reader;
    reader.SetFileName(fileNm.toStdString().c_str());
    if (!reader.Read())
    {        qDebug()<<"Could not read  "<< fileNm;
    }
    //    if (reader.CanRead()==false){
    //        qDebug()<<"is not dicom"<<fileNm;
    //    }
    file = reader.GetFile();
    SetFile(file);
    ds = file.GetDataSet();


    file = reader.GetFile();

    if (!ds.FindDataElement(ptNameTag))
    {
        qDebug()<<"name tag not found";
    }
    displayMetadata();

    //   anonymize();



}


void DCMAnonymizer::anonymize()
{this->RemoveGroupLength();
    this->RemovePrivateTags();

    this->Replace(gdcm::Tag(0x10,0x10),"Anonymous");  //name
    this->Replace(gdcm::Tag(0x10,0x1040),"Street xyz"); //address
    //this->Replace(gdcm::Tag(0x10,0x2154),"00"); //telephone -> throws exception
    qDebug()<<"successfully reamed";


    gdcm::Writer writer;
    writer.SetFile(file);
    writer.SetFileName(fileName.toStdString().c_str());
    if( !writer.Write() )
    {
        qDebug()<<"Writer fail!";

    }

}

void DCMAnonymizer::anonymizeDICOMDIR()
{
    ds = file.GetDataSet();
    fmi = file.GetHeader();

    ms.SetFromFile(file);

        std::stringstream strm;
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
           //do not use GetSequenceOfItems to retrieve items
           gdcm::SmartPointer<gdcm::SequenceOfItems> sqi =de.GetValueAsSQ();
           unsigned int itemused = 1;
           while (itemused<=sqi->GetNumberOfItems())

             {
             strm.str("");

             if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0004, 0x1430)))
               sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0004, 0x1430)).GetValue().Print(strm);

itemused++;
             while((strm.str()=="PATIENT")||((strm.str()=="PATIENT ")))
               {
                 QString tmp = QString::fromStdString(strm.str());

               qDebug() << tmp ;
               strm.str("");
               if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag (0x0010, 0x0010)))
                        std::string mystr = "John Doe";
//                sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0010,0x0010)).SetByteValue( mystr.c_str(), (uint32_t)mystr.size() );

                 sqi->GetItem(itemused).GetDataElement(gdcm::Tag (0x0010, 0x0010)).GetValue().Print(strm);

               tmp = QString::fromStdString(strm.str());
               qDebug() << "PATIENT NAME : " << tmp ;
               itemused++;
             }
             itemused++;
           }

}


}
}

bool DCMAnonymizer::displayMetadata()
{
    std::stringstream strm;
    QString tmp;
    if (!ds.FindDataElement(ptNameTag))
    {
        qDebug()<<"name tag not found";
        return(0);

    }

    gdcm::DataElement outlo=ds.GetDataElement(ptNameTag);

    outlo.GetValue().Print(strm);
    tmp = QString::fromStdString(strm.str());
    qDebug()<<"patient name: " <<tmp;
    return(1);

}
