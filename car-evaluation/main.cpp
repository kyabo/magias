#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//using space
using std::cout; using std::endl;
using std::vector; using std::string;



typedef struct {
  int buy_price;
  int maint_price;
  int doors;
  int persons;
  int lug_boot;
  int safety;
  int class_value;
}cardata;

enum attributes {
  LOW,
  MED,
  HIGH,
  VHIGH,
  MORE
};

enum classes {
  UNACC,
  ACC,
  GOOD,
  VGOOD
};

int convert_class(string value) {
  if (value == "unacc") {
    return 0;
  }

  if (value == "acc") {
    return 1;
  }

  if (value == "good") {
    return 2;
  }

  if (value == "vgood") {
    return 3;
  }

  return -1;
}

int convert_value(string value) {
  if (value == "low" || value == "small") {
    return LOW;
  }

  if (value == "med") {
    return MED;
  }

  if (value == "2") {
    return 2;
  }

  if (value == "3") {
    return 3;
  }

  if (value == "4") {
    return 4;
  }
  
  if (value == "high" || value == "big") {
    return HIGH;
  }

  if (value == "vhigh") {
    return VHIGH;
  }

  if (value == "more" || value == "5more") {
    return MORE;
  }
  
  return -1;
}

vector<int> naive_bayes(vector<cardata> train, vector<cardata> test) {
  vector<int> results;
  
  //c1 = unacc; c2 = acc; c3 = good; c4 = vgood
  float c0 = 0.0, c1 = 0.0, c2 = 0.0, c3 = 0.0, total_size = 0.0;
  float pc0, pc1, pc2, pc3; //P[ci]

  for (vector<cardata>::iterator iter = train.begin();
       iter != train.end(); ++iter) {
    if (iter->class_value == 0) {
      c0++;
    }
    else if (iter->class_value == 1) {
      c1++;
    }
    else if (iter->class_value == 2) {
      c2++;
    }
    else if (iter->class_value == 3) {
      c3++;
    }

    total_size++;
  }

  //Now we calculate P[ci] for each class
  pc0 = c0/total_size;
  pc1 = c1/total_size;
  pc2 = c2/total_size;
  pc3 = c3/total_size;

  
  //Iterate the unknown instances, calculate P[c1|x]
  for (vector<cardata>::iterator iter = test.begin();
       iter != test.end(); ++iter) {

    //reset calculation values.
    float buy_total=0.0, buy_c1=0.0, buy_c2=0.0, buy_c3=0.0, buy_c4=0.0;
    float maint_total=0.0, maint_c1=0.0, maint_c2=0.0, maint_c3=0.0, maint_c4=0.0;
    float doors_total=0.0, doors_c1=0.0, doors_c2=0.0, doors_c3=0.0, doors_c4=0.0;
    float person_total=0.0, person_c1=0.0, person_c2=0.0, person_c3=0.0, person_c4=0.0;
    float lug_total=0.0, lug_c1=0.0, lug_c2=0.0, lug_c3=0.0, lug_c4=0.0;
    float safety_total=0.0, safety_c1=0.0, safety_c2=0.0, safety_c3=0.0, safety_c4=0.0;
  
    
    for (vector<cardata>::iterator iter2 = train.begin();
	 iter2 != train.end(); ++iter2) {
      
      if (iter2->buy_price == iter->buy_price) {
	buy_total++;
	if (iter2->class_value == UNACC) {
	  buy_c1++;
	}

	else if (iter2->class_value == ACC) {
	  buy_c2++;
	}

	else if (iter2->class_value == GOOD) {
	  buy_c3++;
	}

	else if (iter2->class_value == VGOOD) {
	  buy_c4++;
	}
      }

      if (iter2->maint_price == iter->maint_price) {
	maint_total++;
	if (iter2->class_value == UNACC) {
	  maint_c1++;
	}

	else if (iter2->class_value == ACC) {
	  maint_c2++;
	}

	else if (iter2->class_value == GOOD) {
	  maint_c3++;
	}

	else if (iter2->class_value == VGOOD) {
	  maint_c4++;
	}
      }

      if (iter2->doors == iter->doors) {
	doors_total++;
        if (iter2->class_value == UNACC) {
	  doors_c1++;
	}

	else if (iter2->class_value == ACC) {
	  doors_c2++;
	}

	else if (iter2->class_value == GOOD) {
	  doors_c3++;
	}

	else if (iter2->class_value == VGOOD) {
	  doors_c4++;
	}
      }

      if (iter2->persons == iter->persons) {
	person_total++;
        if (iter2->class_value == UNACC) {
	  person_c1++;
	}

	else if (iter2->class_value == ACC) {
	  person_c2++;
	}

	else if (iter2->class_value == GOOD) {
	  person_c3++;
	}

	else if (iter2->class_value == VGOOD) {
	  person_c4++;
	}
      }

      if (iter2->lug_boot == iter->lug_boot) {
	lug_total++;
        if (iter2->class_value == UNACC) {
	  lug_c1++;
	}

	else if (iter2->class_value == ACC) {
	  lug_c2++;
	}

	else if (iter2->class_value == GOOD) {
	  lug_c3++;
	}

	else if (iter2->class_value == VGOOD) {
	  lug_c4++;
	}
      }

      if (iter2->safety == iter->safety) {
	safety_total++;
        if (iter2->class_value == UNACC) {
	  safety_c1++;
	}

	else if (iter2->class_value == ACC) {
	  safety_c2++;
	}

	else if (iter2->class_value == GOOD) {
	  safety_c3++;
	}

	else if (iter2->class_value == VGOOD) {
	  safety_c4++;
	}
      }

      //pausa da alegria
      
      
    }

    //end of inner for. calculate values:
    float final_c0, final_c1, final_c2, final_c3;

    c0 = (buy_c1/buy_total) * (maint_c1/maint_total) *
      (doors_c1/doors_total) * (person_c1/person_total) *(lug_c1/lug_total) *
      (safety_c1/safety_total);

    c1 = (buy_c2/buy_total) * (maint_c2/maint_total) *
      (doors_c2/doors_total) * (person_c2/person_total) *(lug_c2/lug_total) *
      (safety_c2/safety_total);

    c2 = (buy_c3/buy_total) * (maint_c3/maint_total) *
      (doors_c3/doors_total) * (person_c3/person_total) *(lug_c3/lug_total) *
      (safety_c3/safety_total);

    c3 = (buy_c4/buy_total) * (maint_c4/maint_total) *
      (doors_c4/doors_total) * (person_c4/person_total) *(lug_c4/lug_total) *
      (safety_c4/safety_total);

    final_c0 = c0 * pc0;
    final_c1 = c1 * pc1;
    final_c2 = c2 * pc2;
    final_c3 = c3 * pc3;

    float max = c0;
    int the_class;
    
    if (c1 > max) {
      max = c1;
    }

    if (c2 > max) {
      max = c2;
    }

    if (c3 > max) {
      max = c3;
    }
    
    if (max == c0) {
      the_class = UNACC;
    }
    
    if (max == c1) {
      the_class = ACC;
    }

    if (max == c2) {
      the_class = GOOD;
    }

    if (max == c3) {
      the_class = VGOOD;
    }

    results.push_back(the_class);
    //end of outer loop.
  }

  return results;
}

vector<cardata> get_data_from_file(std::string filename, bool get_class) {

  int buy_price, maint_price, doors, persons, lug_boot, safety, class_value;

  vector<cardata> car_data;
  
  std::ifstream f(filename);
  string line, value;
  if (!f) {
      std::cout << "FILE NOT FOUNDDDDD\n";
      return car_data;
  }

  while (getline(f, line)) { //get contents from ALL lines.
    
    std::stringstream linestream(line);
    getline(linestream, value, ','); //get buy_price.
    buy_price = convert_value(value);
    
    getline(linestream, value, ','); //get maint_price.
    maint_price = convert_value(value);
    
    getline(linestream, value, ','); //get num doors.
    doors = convert_value(value);
    
    getline(linestream, value, ','); //get num person.
    persons = convert_value(value);
    
    getline(linestream, value, ','); //get lugage boot.
    lug_boot = convert_value(value);
    
    getline(linestream, value, ','); //get safety.
    safety = convert_value(value);
    
    if (get_class) {
      getline(linestream, value, ','); //get class.
      class_value = convert_class(value);
    }
    
    //set values for instance.
    cardata car;
    car.buy_price = buy_price;
    car.maint_price = maint_price;
    car.doors = doors;
    car.persons = persons;
    car.lug_boot = lug_boot;
    car.safety = safety;
    if (get_class) {
      car.class_value = class_value;
    }
    else {
      car.class_value = -1;
    }
    
    car_data.push_back(car);
  }

  return car_data;
  
}


float calc_precision(vector<int> res, vector<cardata> real) {
  float correct = 0.0, total;
  for (int i = 0; i < real.size(); i++) {
    if (res[i] == real[i].class_value) {
      correct++;
    }
  }

  total = real.size();
  return correct/total;
}

int main() {
  vector<cardata> train;
  vector<cardata> test;
  vector<cardata> realtest;
  
  string train_file = "train3.data";
  string test_file = "test.data";
  
  train = get_data_from_file(train_file, 1);
  test = get_data_from_file(test_file, 0);
  realtest = get_data_from_file(test_file, 1);

  vector<int> results;
  
  results = naive_bayes(train, test);

  float hit_ratio = 0.0;
  hit_ratio = calc_precision(results, realtest);
  hit_ratio = hit_ratio * 100;

  for (vector<int>::const_iterator iter = results.begin();
       iter != results.end(); ++iter) {
    cout << (*iter) << endl;
  }
  cout << "The precision was: " << hit_ratio << "%"<< endl;
  
  return 0;
}
