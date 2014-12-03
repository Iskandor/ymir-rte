/* 
 * File:   DataSetUtils.h
 * Author: matej
 *
 * Created on July 23, 2012, 9:03 PM
 */

#ifndef DATASETUTILS_H
#define	DATASETUTILS_H

#include "DataSet.h"

class DataSetUtils {
public:
    DataSetUtils();
    DataSetUtils(const DataSetUtils& orig);
    virtual ~DataSetUtils();
private:
    double vector_magnitude(vector<float> *v);

public:
    void analyze_vector_norms(CDataSet *dataset);
    void integrity_check(CDataSet *dataset);
};

#endif	/* DATASETUTILS_H */

