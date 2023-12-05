#include "Hash.h"

template<typename Comparable>
bool Hash<Comparable>::isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

template <typename Comparable>
int Hash<Comparable>::nextPrime(int n)
{
    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

template <typename Comparable>
Hash<Comparable>::Hash() {
    //According to the test cases values size started by 53.
    sizeOfArray = 53;
    loadFactor = 0;
    itemCount = 0;
    hashArray.resize(53); //HashEntry's constructed with their default constructor,
                           // all set to "EMPTY" situation
}


//This function uses polynomial rolling hash technique
template<typename Comparable>
long long Hash<Comparable>::doHash(Comparable str, int sizeOfArray) {

   
    

    string fullName = string(str);


    long long p = 31;
    long long hashValue = 0;
    
    long long powerP = 1;
   
    
    //For each letter we use ASCII values and multiply with the powers of p'
    //in order to avoid overflow, we get the modulo of the sizeOfArray
    for (int i = 0; i < fullName.length(); i++) {

        

        //We consider only the letters
        if (isalpha(fullName[i])) {
            //to ignore white spaces or any other non-alphabetical
            hashValue = (hashValue + (fullName[i] - 'A' + 1) * powerP) % sizeOfArray;
            powerP = (powerP * p) % sizeOfArray;
        }


        
    }
    return hashValue;

}

template<typename Comparable>
void Hash<Comparable>::reHash()
{


    vector<HashEntry<Comparable>> prevArray = this->hashArray;

    // Create new double-sized, empty table
    this->hashArray.resize(nextPrime(2 * prevArray.size()));

    //starting from scratch by setting all entries as empty in our newly resized array
    for (int j = 0; j < this->hashArray.size(); j++)
        this->hashArray[j].situation = "EMPTY";

    //updating our size
    sizeOfArray = nextPrime(2 * sizeOfArray);

    //in order for not to have recursive problem in inserting hash
    //we need to update our loadFactor and item count to have a fresh start
    itemCount = 0;


    loadFactor = double(itemCount) / double(sizeOfArray);




    for (int i = 0; i < prevArray.size(); i++) {

        //inserting our active elements in our previous array to newly designed array
        if (prevArray[i].situation == "ACTIVE") {

            Comparable fullName = prevArray[i].fullName;
            Comparable phoneNumber = prevArray[i].phoneNumber;
            Comparable city = prevArray[i].city;

            this->insertHash(fullName, phoneNumber, city);
        }

    }

   
    

    cout << "REHASHED..." << endl;
    cout << "Previous table size: " << prevArray.size() << ", new table size: " << sizeOfArray
        << ", current unique word count: " << itemCount << ", current load factor: " << loadFactor << endl;

}

template <typename Comparable>
bool Hash<Comparable>::searchHash(Comparable fullName) {
    //We are going to use quadratic probing

    int hashValue = doHash(fullName, this->sizeOfArray);

    int increment = 1;

    while (hashArray[hashValue].situation != "EMPTY") {
        if (hashArray[hashValue].fullName == fullName) {
            //then this means we found the contact BUT it might be DELETED before
            //because in DELETE process we are not updating our info as NONE or etc.

            //check whether it is DELETED or not
            if (hashArray[hashValue].situation != "DELETED") {
                cout << hashArray[hashValue].fullName << " " << hashArray[hashValue].phoneNumber
                    << " " << hashArray[hashValue].city << endl;
                
                return true;
            }

        }
        //quadratic probing  +1 + 4 + 9 +16 ....
        hashValue = (hashValue + int(pow(increment, 2))) % sizeOfArray;
        increment++;
    }

    return false;


}



template<typename Comparable>
void Hash<Comparable>::searchHashWithoutPrint(Comparable fullName)
{
    //We are going to use quadratic probing

    int hashValue = doHash(fullName, this->sizeOfArray);
    int hashValue2 = hashValue;


    int increment = 1;

    while (hashArray[hashValue].situation != "EMPTY") {
        if (hashArray[hashValue].fullName == fullName) {
            //then this means we found the contact BUT it might be DELETED before
            //because in DELETE process we are not updating our info as NONE or etc.

            //check whether it is DELETED or not
            if (hashArray[hashValue].situation != "DELETED") {
                //cout << hashArray[hashValue].fullName << " " << hashArray[hashValue].phoneNumber
                  //  << " " << hashArray[hashValue].city << endl;
                break;
            }

        }

        hashValue = (hashValue + int(pow(increment, 2))) % sizeOfArray;
        increment++;

        if (hashValue2 == hashValue) {
            //if we get back to the same value, meaning that there is no empty place
            //to get away with the infinite loop, we exit

            //this case is not expected due to the technique we used but in case sth happens
            //we take our measure
            break;
        }

    }


}

template<typename Comparable>
bool Hash<Comparable>::insertHash(Comparable fullName,Comparable phoneNumber,Comparable city){
    int hashValue = doHash(fullName,this->sizeOfArray);
    
    //this is for quadratic probing after we make sure that the element is not already in table
    int hashValue2 = hashValue;




    int increment = 1;

    bool isAlreadyThere = false;


    //we need to search through the table to make sure if we have that element already.
    //so we should not insert our value whenever we see DELETED. We need to search
    //until we see EMPTY so that we can definitely say the element is not already there.

    while (hashArray[hashValue].situation!="EMPTY") {
        if (hashArray[hashValue].fullName == fullName && hashArray[hashValue].situation=="ACTIVE") {
            // if it is the reason that we get out of the loop,
            //then this means we have already this contact,
            //so we can leave it as it is
            isAlreadyThere = true;
            break;
        }
        else {
            hashValue = (hashValue + int(pow(increment, 2))) % sizeOfArray;
            increment++;
        }
        if (hashValue2 == hashValue) {
            //if we get back to the same value, meaning that there is no empty place
            //to get away with the infinite loop, we exit

            //this case is not expected due to the technique we used but in case sth happens
            //we take our measure
            return false;
        }

       
    }



    int increment2 = 1;
    

    if (!isAlreadyThere) {
        //that means the element is not already in the list. So we need to do probing
        //once more by considering DELETED ones as available points along with EMPTY's

        while (hashArray[hashValue2].situation=="ACTIVE") {
            
             hashValue2 = (hashValue2 + int(pow(increment2, 2))) % sizeOfArray;
             increment2++;
        


        }
        //Now at this point we either find EMPTY or DELETED

        hashArray[hashValue2].situation = "ACTIVE";
        hashArray[hashValue2].fullName = fullName;
        hashArray[hashValue2].phoneNumber = phoneNumber;
        hashArray[hashValue2].city = city;
        //updating fields accordingly
        itemCount++;
        loadFactor = double(itemCount) / double(sizeOfArray);

        if (loadFactor > LOAD_FACTOR_LIMIT) {
            this->reHash();
        }
        return true;

    }
    else {
        return false;
    }
  
 
    
}

template<typename Comparable>
bool Hash<Comparable>::deleteHash(Comparable fullName){

    int hashValue = doHash(fullName, this->sizeOfArray);

    int initialHashValue = hashValue;

    int increment=1;

    
    while (hashArray[hashValue].situation != "EMPTY") {
        if (hashArray[hashValue].fullName == fullName &&
            hashArray[hashValue].situation=="ACTIVE") {
           
            //then this means we found the contact
            hashArray[hashValue].situation = "DELETED";
            
            //the rest is not important since we're going to treat
            // DELETED ones as available spaces while inserting
            //and we're going to put new values for fullName, phoneNumber and city

            //updating fields accordingly
            itemCount--;
            loadFactor = double(itemCount) / double(sizeOfArray);
            return true;
           

        }
        

        hashValue = (hashValue + int(pow(increment, 2))) % sizeOfArray;
        increment++;

        if (initialHashValue == hashValue) {
            //if we circle around the array 1 round, in order to get rid of infinite loop
            //we exit

            return false;
        }

    }
    //we find an empty location,this means we cannot find it
    return false;
    


    

}
