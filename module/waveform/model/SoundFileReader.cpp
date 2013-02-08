//
//  SoundFileReader.cpp
//  autioData
//
//  Created by BO CUNPU on 12-10-18.
//  Copyright (c) 2012年 BO CUNPU. All rights reserved.
//

#include "SoundFileReader.h"
#include <cmath>


#define absX(x) (x<0?0-x:x)
#define minMaxX(x,mn,mx) (x<=mn?mn:(x>=mx?mx:x))
#define noiseFloor (-50.0)
#define decibel(amplitude) (20.0 * log10(absX(amplitude)/32767.0))
#define imgExt @"png"
#define imageToData(x) UIImagePNGRepresentation(x)


using namespace std;


SoundFileReader::SoundFileReader()
{
    
}

SoundFileReader::~SoundFileReader()
{
    delete [] m_aFileName;
}

//############################################################################################################//
void SoundFileReader::loadMusicFile(const char* aFileName,BasicSoundInfo info)
{
    m_aFileName = aFileName;
    m_soundInfo = info;
    
    ifstream filestr;
    
    filestr.open (m_aFileName,ifstream::binary);
    if (filestr.is_open())
    {
        // get size of file
        long size;
        
        //determine the size of the file
        filestr.seekg(0,ifstream::end);
        size=filestr.tellg();
        filestr.seekg(0);
        cout << "File "<< m_aFileName <<" loaded successfully.\n";
        cout << "File size: " << size <<" bytes. \n" <<endl;
    }
    else
    {
        cout << "Error, when loading the file! Please try again! \n";

    }
    filestr.close();
 
}

//############################################################################################################//
void SoundFileReader::printOutNormalizedLeftAndRight(int sampleRate)
{
    int bufferSize  = 0;
    float * buffer = readRawDataFromMusic(sampleRate,bufferSize);
    
    //normalize the results into a 0 - 100 scale
    for (int i = 0; i < bufferSize; i+=2)
    {
        cout <<i / 2<<": "<<100 - (buffer[i] / (-50) * 100) <<" "<< 100 - (buffer[i + 1] / (-50) * 100) << endl;
    }
    
}

//############################################################################################################//
void SoundFileReader::outputNormalizedLeftAndRightToFile(const char * outputFileName, int sampleRate)
{
    int bufferSize  = 0;
    float * buffer = readRawDataFromMusic(sampleRate,bufferSize);
    
    ofstream outfilestr;
    outfilestr.open(outputFileName);
    //normalize the results into a 0 - 100 scale
    for (int i = 0; i < bufferSize; i+=2)
    {
        outfilestr  <<100 - (buffer[i] / (-50) * 100) << endl;
    }
    cout << "Normalized left and right wrote to " << outputFileName << " successfully." << endl;
    outfilestr.close();
}


//############################################################################################################//
float * SoundFileReader::outputNormalizedAverageToBuffer(int & theBufferSize, int sampleRate)
{
    int bufferSize  = 0;
    float * buffer = readRawDataFromMusic(sampleRate,bufferSize);
    
    theBufferSize = bufferSize / 2;

    int newSamplecount = bufferSize / 2;
    
    

    float aveRight = 0;
    float aveLeft = 0;
    float rightBuffer[bufferSize];
    float leftBuffer[bufferSize];  

    for (int i = 0; i < bufferSize; i+=2)
    {
        aveRight += 100 - (buffer[i + 1] / (-50) * 100);
        rightBuffer[i / 2] =  100 - (buffer[i + 1] / (-50) * 100);

        aveLeft += 100 - (buffer[i] / (-50) * 100);
        leftBuffer[i / 2] = 100 - (buffer[i] / (-50) * 100);
    }
    aveRight = aveRight / newSamplecount;
    aveLeft = aveLeft / newSamplecount;
    //cout << "Average Right: " << ave << endl;
    float factorRight = 50.0 / aveRight;
    float factorLeft = 50.0 / aveLeft;

    int resultRight = 0;
    int resultLeft = 0;
    int resultAve = 0;
    
    int low = 0;
    int high = 0;

    float * resultArray = new float[newSamplecount];

    for (int i = 0; i < newSamplecount; i++)
    {
        resultRight = rightBuffer[i] * factorRight;
        resultLeft = leftBuffer[i] * factorLeft;
        resultAve = (resultRight + resultLeft) / 2;
       
        if (resultAve < 0)
             resultAve = 1;
        if (resultAve > 100)
             resultAve = 100;
        
        if (resultAve < 50)
            low++;
        if (resultAve > 50)
            high++;
        
        resultArray[i] = resultAve;
    }

    return resultArray;
}

//############################################################################################################//
 void SoundFileReader::outputNormalizedLeftToFile(const char * outputFileName, int sampleRate)
{
    int bufferSize  = 0;
    float * buffer = readRawDataFromMusic(sampleRate,bufferSize);

    int newSamplecount = bufferSize / 2;
    
    ofstream outfilestr;
    outfilestr.open(outputFileName);
    //normalize the results into a 0 - 100 scale
    
    float ave = 0;
    float leftBuffer[bufferSize];
    for (int i = 0; i < bufferSize; i+=2)
    {
        ave += 100 - (buffer[i] / (-50) * 100);
        leftBuffer[i / 2] =  100 - (buffer[i] / (-50) * 100);
    }
    ave = ave / newSamplecount;
    //cout << "Average Right: " << ave << endl;
    float factor = 50.0 / ave;
    int result = 0;
    
    int low = 0;
    int high = 0;

    for (int i = 0; i < newSamplecount; i++)
    {
        result = leftBuffer[i] * factor;
        if (result < 0)
             result = 1;
        if (result > 100)
             result = 100;
        
        if (result < 50)
            low++;
        if (result > 50)
            high++;
        
        outfilestr << result << endl;
    }

    cout << "Low: " << low << " High: " << high << endl;
    
    cout << "Normalized left wrote to " << outputFileName << " successfully." << endl;
    outfilestr.close();


}



//############################################################################################################//
 void SoundFileReader::outputNormalizedRightToFile(const char * outputFileName, int sampleRate)
{
    int bufferSize  = 0;
    float * buffer = readRawDataFromMusic(sampleRate,bufferSize);
    
    int newSamplecount = bufferSize / 2;
    
    
    ofstream outfilestr;
    outfilestr.open(outputFileName);
    //normalize the results into a 0 - 100 scale
    
    float ave = 0;
    float rightBuffer[bufferSize];
    for (int i = 0; i < bufferSize; i+=2)
    {
        ave += 100 - (buffer[i + 1] / (-50) * 100);
        rightBuffer[i / 2] =  100 - (buffer[i + 1] / (-50) * 100);
    }
    ave = ave / newSamplecount;
    //cout << "Average Right: " << ave << endl;
    float factor = 50.0 / ave;
    int result = 0;
    
    int low = 0;
    int high = 0;

    for (int i = 0; i < newSamplecount; i++)
    {
        result = rightBuffer[i] * factor;
        if (result < 0)
             result = 1;
        if (result > 100)
             result = 100;
        
        if (result < 50)
            low++;
        if (result > 50)
            high++;
        
        outfilestr << result << endl;
    }

    cout << "Low: " << low << " High: " << high << endl;
    
    cout << "Normalized right wrote to " << outputFileName << " successfully." << endl;
    outfilestr.close();
}


















float * SoundFileReader::readRawDataFromMusic(int sampleRate, int & sizeOfBuffer)
{
    int numOfChannels = m_soundInfo.numOfChannels,  samplesRate = m_soundInfo.sampleRate;
    int newSampleRate = sampleRate;
    
    ifstream filestr;
    
    filestr.open (m_aFileName,ifstream::binary);
    
    // >> i/o operations here <<
    if (filestr.is_open())
        cout << m_aFileName <<" opened successflly.\n";
    else
    {
        cout << "Error, when opening the file!\n";
        return NULL;
    }
    
    // get size of file
    long size;
    filestr.seekg(0,ifstream::end);
    size=filestr.tellg();
    filestr.seekg(0);
    
    //since 44100Hz is too high for our purpose, we need to lower our sample rate.
    //For convenvice, the denominator here is just our desired sample rate; here,
    //it is set to 50Hz, meanning that the samples are taken every 0.02s.
    int numOfOldSamplesForOneNewSample = samplesRate / newSampleRate;
    
    int numOfOldSamples = size / sizeof(short) / numOfChannels;
    int numOfNewSamples = numOfOldSamples / numOfOldSamplesForOneNewSample;
    int bufferSize = numOfNewSamples * numOfChannels;
    float * buffer = new float [bufferSize];
    int index = 0;
    
    
    float totalLeft = 0;
    float totalRight = 0;
    int newSamplecount = 0;
    int oldSampleCount = 0;
    
    short aSample;
    float left = 0;
    float right = 0;
    
    float normalizeMax = noiseFloor;
    
    //read the raw music date from tht wave file
    while (!filestr.eof())
    {
        
        //process the left channel
        filestr.read((char*)&aSample,sizeof(aSample));
        left = (float)aSample;
        //left = decibel(left);
        //left = minMaxX(left,noiseFloor,0);
        totalLeft += left;
        
        //process the right channel
        filestr.read((char*)&aSample,sizeof(aSample));
        right = (float)aSample;
        //right = decibel(right);
        //right = minMaxX(right,noiseFloor,0);
        totalRight += right;
        
        oldSampleCount++;
        
        if (oldSampleCount > numOfOldSamplesForOneNewSample)
        {
            //calculate the left value in this frame at our sample rates
            left  = totalLeft / oldSampleCount;
            if (left > normalizeMax) {
                normalizeMax = left;
            }
            buffer[index++] = left;
            //cout << left << endl;
            
            //calculate the left value in this frame at our sample rates
            right = totalRight / oldSampleCount;
            if (right > normalizeMax) {
                normalizeMax = right;
            }
            buffer[index++] = right;
            
            //reset the left and the right
            totalLeft   = 0;
            totalRight  = 0;
            oldSampleCount = 0;

            newSamplecount++;
        }
    }
    filestr.close();

    sizeOfBuffer = bufferSize;
    return buffer;

}






