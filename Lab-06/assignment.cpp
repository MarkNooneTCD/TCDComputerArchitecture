// Title: LKN Cache Simulation, Author: Mark Noone Username: manoone
// Date: 15th December 2017

#define FILE_NAME "/Users/marcus/Desktop/Gits/TCDComputerArchitecture/Lab-06/gcc1.trace"
#define ADDRESS_MASK 0x007FFFFF // The mask used to get the first 23 bits of the word.
#define ADDRESS_SHIFT 2         // Need to shift by two bit posiitons as
                                // the first two bits in the address are always zero
#define BURST_MASK 3            // Extracts the burst value from the word.
#define BURST_SHIFT 27          // puts the word at the start of the int to get the
                                // proper value.
#define TYPE_MASK 7             // Mask to get the address type value
#define TYPE_SHIFT 2            // Mask to shift address type value to LSB
#define IR 4                    // Status code value for Instruction Read
#define DR 6                    // Status code value for Data Read
#define DW 7                    // Status code value for Data Write.
#define SET_NUMBER_SHIFT 4      // Number of bits to shift to get the set number to LSB
#define OFFSET_MASK 15          // Mask to get the offset from an address

#include <fstream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <bitset>
#include <math.h>               // Log2

using namespace std;

// No longer needed but handy to have to fully implement the cache.
class CacheBlock
{
  public:
  int *arr;
  int blockWords;

  CacheBlock(int blockWords){
    arr= new int[blockWords];
    this->blockWords = blockWords;
  }

  int getWord(int offset){
    return arr[offset/blockWords];
  }
};

class Cache
{
  public:
  int l, k, n;
  int SET_NUMBER_MASK;
  int TAG_SHIFT;


  Cache(int l, int k, int n){
    this->l = l;
    this->k = k;
    this->n = n;
    cacheData = new int*[n];
    lruData = new int* [n];

    // Get the amount of bits needed to specify the set
    TAG_SHIFT = log2(n);
    // cout << "log2 ans " << TAG_SHIFT << "\n";

    // Get the TAG_SHIFT bits except all as 1's to make a mask
    SET_NUMBER_MASK = (pow(2, TAG_SHIFT) -1);
    // cout << "Set Number mask is " << SET_NUMBER_MASK << "\n";

    for(int i = 0; i < n; ++i){
      cacheData[i] = new int[k];
      for(int j = 0; j < k; ++j)
        cacheData[i][j] = -1;
    }

    // Initialise LRU tracking with -1 values.
    for(int x = 0; x < n; ++x){
      lruData[x] = new int[k];
      for(int y = 0; y < k; y++){
        lruData[x][y] = -1;
      }
    }
  }

  void printCache() {
    printf("L: %d, K: %d, N: %d \n", l, k, n);
  }

  void hit(unsigned int address, unsigned int burst_count){
    // bitset<32> bitset1(address);
    int offset = address & OFFSET_MASK;
    // cout << bitset1 << endl;
    // bitset<32> bitset2(offset);
    // cout << bitset2 << endl;
    int set_num = (address >> SET_NUMBER_SHIFT) & SET_NUMBER_MASK;
    // bitset<32> bitset3(set_num);
    // cout << bitset3 << endl;
    int tag = address >> (SET_NUMBER_SHIFT+TAG_SHIFT);
    // bitset<32> bitset4(tag);
    // cout << bitset4 << endl;
    int *tmp = cacheData[set_num];
    bool hasHit = false;
    for(int i = 0; i < 4; i++){
      if(tag == tmp[i]){
        hits++;
        // cout << address << endl;
        hasHit = true;
        break;
      }
    }
    if(hasHit){
      hits += burst_count;
    } else {
      miss++;
      int oldest_tag = lruData[set_num][k-1];
      for(int i = k-1; i > 0; i--){
        lruData[set_num][i] = lruData[set_num][i-1];
      }
      lruData[set_num][0] = tag;
      bool tagFound = false;
      for(int j = 0; j < k; j++){
        if(tmp[j] == oldest_tag){
          tmp[j] = tag;
          tagFound = true;
          break;
        }
      }
      if(!tagFound){
        cerr << "Tag Not Found from LRU spec." << endl;
      }

    }
  }

  int getHits(){
    return hits;
  }

  int getMisses(){
    return miss;
  }

  int getMemAccesses(){
    return miss+hits;
  }

  float percentageHitRate(){
    return ((float) hits / (float)(miss+hits))*100;
  }

  private:
    int **cacheData;
    int **lruData;
    int hits =0;
    int miss =0;

};

int main(int argc, char *argv[])
{
    int reverseFlag = 0;
    if(argc > 1) {
      std::string reverseString = argv[1];
      reverseFlag = 0;
      if(reverseString == "reverse"){
        cout << "Reversing bits is set .." << endl;
        reverseFlag = 1;
      }
    }


    Cache instructionCache(16, 1, 1024);
    Cache dataCache(16, 8, 256);
    unsigned int ReverseBits(unsigned int input);

    // Cache Testing
    // Fetching Addresses
    // 0000 0001 1111 1111 1111 0010 0110 0000 - 0x1FFF260 - 33550944 (Miss)
    // 0000 0001 1111 0000 1111 0000 0101 0000 - 0x1F0F050 - 32567376 (Miss)
    // 0000 0000 0000 0000 0000 0000 0001 0000 - 0x0000010 - 16       (Miss)
    // 0000 0000 0000 0000 0001 0000 0010 0000 - 0x0001020 - 4128     (Miss)
    // 0000 0001 1111 1111 1111 0010 0110 0000 - 0x1FFF260 - 33550944 (Hit)
    // 0000 0001 1111 0000 1111 0000 0101 0000 - 0x1F0F050 - 32567376 (Hit)
    // Should have 2 hits and 4 misses
    // dataCache.hit(33550944, 0);
    // dataCache.hit(32567376, 0);
    // dataCache.hit(16, 0);
    // dataCache.hit(4128, 0);
    // dataCache.hit(33550944, 0);
    // dataCache.hit(32567376, 0);

    // printf("Data Cache. Hits: %d, Misses: %d, Total: %d, Percentage Hit Rate: %d \n",dataCache.getHits(), dataCache.getMisses(),
    //         dataCache.getMemAccesses(), (dataCache.getHits() / dataCache.getMemAccesses()));

    // Open the trace file.
    std::ifstream input( FILE_NAME, std::ios::binary );

    // Copy all data into buffer
    std::vector<char> buffer((
            std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

    // Calculate integers
    for(int i = 0; i < buffer.size(); i+=4){
      unsigned int tot = buffer.at(i);
      tot = (tot << 8 )+ buffer.at(i+1);
      tot = (tot << 8 )+ buffer.at(i+2);
      tot = (tot << 8 )+ buffer.at(i+3);
      // printf("Int Is: %04x \n", tot);
      if(reverseFlag == 1)
        tot = ReverseBits(tot);
      // printf("Int Is: %04x \n", tot);

      unsigned int a = (tot & ADDRESS_MASK) << ADDRESS_SHIFT;
      // printf("A Is: %04x \n", a);
      // printf("Tot Is: %04x \n", tot);
      unsigned int sfd = tot;
      unsigned int burst_count = ((tot >> BURST_SHIFT) & BURST_MASK)+1;
      // printf("Burst Is: %04x \n", burst_count);
      unsigned int type = (tot >> (TYPE_SHIFT+BURST_SHIFT)) & TYPE_MASK;
      // printf("Type Is: %04x \n", type);
      switch(type){
        case IR:
            instructionCache.hit(a, burst_count);
            break;
        case DR:
        case DW:
            dataCache.hit(a, burst_count);
            break;
        // default:
            // cout << "No switch taken" << endl;
      }

    }

    // Complete The Progam and Close all files.
    printf("Instruction Cache. Hits: %d, Misses: %d, Total: %d, Percentage Hit Rate: %f \n",instructionCache.getHits(),
            instructionCache.getMisses(), instructionCache.getMemAccesses(), instructionCache.percentageHitRate());
    printf("Data Cache. Hits: %d, Misses: %d, Total: %d, Percentage Hit Rate: %f \n",dataCache.getHits(), dataCache.getMisses(),
            dataCache.getMemAccesses(), dataCache.percentageHitRate() );
    return 0;
}

unsigned int ReverseBits(unsigned int input)
{
    unsigned int output = input;
    for (int i = sizeof(input) * 8-1; i; --i)
    {
        output <<= 1;
        input  >>= 1;
        output |=  input & 1;
    }
    return output;
}
