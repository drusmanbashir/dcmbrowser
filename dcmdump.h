#ifndef DCMDUMP_H
#define DCMDUMP_H


#include <gdcmReader.h>
#include <gdcmMediaStorage.h>
#include <QString>

typedef std::set<gdcm::DataElement> DataElementSet;
typedef DataElementSet::const_iterator ConstIterator;

class DCMDump{

public:

    DCMDump(const QString& dcmFile);
    void parse();
    QString outputPtID();
    QString outputModality();
    QString outputStudydate();


private:


  std::stringstream strm;
    gdcm::File file;
    gdcm::DataSet ds;
    gdcm::FileMetaInformation fmi ;

    gdcm::MediaStorage ms;

    QString ptID;
    QString modality;
    QString studyDate;

};



class DirectoryParser{
public:
    DirectoryParser();

private:

};

#endif // DCMDUMP_H

