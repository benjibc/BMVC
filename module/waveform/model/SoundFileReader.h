//
//  SoundFileReader.h
//  autioData
//
//  Created by BO CUNPU on 12-10-18.
//  Copyright (c) 2012年 BO CUNPU. All rights reserved.
//

#ifndef __autioData__SoundFileReader__
#define __autioData__SoundFileReader__

#include <iostream>
#include <fstream>

using namespace std;

#define absX(x) (x<0?0-x:x)
#define minMaxX(x,mn, mx) (x<mn?mn:(x>=mx?mx:x))
#define noiseFloor (-50.0)

struct BasicSoundInfo
{
    int numOfChannels;
    int sampleRate;
    int bitsPerSample;
    BasicSoundInfo() {numOfChannels = 2;sampleRate = 44100;bitsPerSample = 16;};
};


class SoundFileReader
{
public:
    SoundFileReader();
    ~SoundFileReader();
    
    void loadMusicFile(const char* aFileName = "",BasicSoundInfo info = BasicSoundInfo());
    float * outputNormalizedAverageToBuffer(int & bufferSize ,float sampleRate);
    
    //print out the numeric repesentation of the sound file; two number each line, left and right channel; scaled between 0 and 100.
    //sampleRate is the desired sample rate in Hz, for instance, 50Hz means that samples are taken every 0.02s
    //void printOutNormalizedLeftAndRight(int sampleRate);
    //output the result above to a file
    //void outputNormalizedLeftAndRightToFile(const char * outputFileName, int sampleRate);
    //void outputNormalizedLeftToFile(const char * outputFileName, int sampleRate);
    //void outputNormalizedRightToFile(const char * outputFileName, int sampleRate);
    //output the result above the buffer
 private:
    const char* m_aFileName;
    BasicSoundInfo m_soundInfo;

    float * readRawDataFromMusic(float sampleRate, int & sizeOfBuffer);
};


inline
SoundFileReader::SoundFileReader()
{
    
}

inline
SoundFileReader::~SoundFileReader()
{
    delete [] m_aFileName;
}


inline
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

inline
float * SoundFileReader::readRawDataFromMusic(float sampleRate, int & sizeOfBuffer)
{
    int numOfChannels = m_soundInfo.numOfChannels,  samplesRate = m_soundInfo.sampleRate;
    float newSampleRate = sampleRate;
    
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
    float numOfOldSamplesForOneNewSample = samplesRate / newSampleRate;
    
    int numOfOldSamples = size / sizeof(short) / numOfChannels;
    int numOfNewSamples = numOfOldSamples / numOfOldSamplesForOneNewSample;
    int bufferSize = numOfNewSamples * numOfChannels;
    float * buffer = new float [bufferSize];
    int index = 0;

    //cout << bufferSize << " " << numOfOldSamplesForOneNewSample << " " << newSampleRate  << endl; 
    
    
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




#endif /* defined(__autioData__SoundFileReader__) */
