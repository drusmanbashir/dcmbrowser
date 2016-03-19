#ifndef DCMANONYMIZER_H
#define DCMANONYMIZER_H
#include <gdcmReader.h>
#include <gdcmMediaStorage.h>
#include <QString>
#include <gdcmAnonymizer.h>

using namespace gdcm;

class DCMAnonymizer : public Anonymizer

{
public:
    DCMAnonymizer(const QString& fileNm);
    void anonymize();
    void anonymizeDICOMDIR();
    bool displayMetadata();

private:
    QString fileName;

    gdcm::File file;

    gdcm::Tag ptNameTag;


    std::stringstream strm;
      gdcm::DataSet ds;
      gdcm::FileMetaInformation fmi ;
   gdcm::MediaStorage ms;

};



#endif // DCMANONYMIZER_H

