#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
clock_t startTime = clock();
void set_random_seed();
int randn(int n);

void print(std::vector<int> ha);

struct mm_code_maker{
    
    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
    }
    
    void generate_sequence(){
        for(int i = 0; i < length; i++){
            sequence.push_back(randn(num));
        }
    }
    void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){
        std::vector<int> timesSequence, timesAttempt;
        int total_hits = 0;
        black_hits = 0;
        white_hits = 0;
        
        for (int i = 0; i < num; i++) {
            timesSequence.push_back(0);
            timesAttempt.push_back(0);
        }
        
        for (int i = 0; i < length; i++) {
            if (attempt[i] == sequence[i]) {
                black_hits++;
            }
            
            timesSequence[sequence[i]]++;
            timesAttempt[attempt[i]]++;
        }
        
        for (int i = 0; i < num; i++) {
            total_hits += std::min(timesSequence[i],timesAttempt[i]);
        }
        
        white_hits = total_hits - black_hits;
        
    }
    std::vector<int> sequence;
    
    int length;
    int num;
};
struct mm_solver{
    
    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
        posn = 0;
        black = 0;
        po = 0;
        determine = false;
        count_b_n=0;
        next_element =0;
        totalblack=0;
        totalwhite=0;
        stage = 1;
        count_w=0;
        count_w_n=0;
        check_white_process = false;
        totalwhite_taken=false;
        black2=0;
        be_processed =false;
        attempts = 0;
        comb=0;
        order_combv=0;
        new_pool=true;
        nextstart =0;
        
        
        
        comb=3;
        if(length==8){
            for(int i =0;i<2;i++){
                combv.push_back(4);
            }
        }
        if(length==12){
            for(int i=0;i<3;i++){
                combv.push_back(4);
            }
        }
        if(length==14){
            for(int i=0;i<4;i++){
                if(i==0||i==1){
                    combv.push_back(4);
                }
                else{
                    combv.push_back(3);
                }
            }
        }
        if(length==9){
            for(int i=0;i<2;i++){
                if(i==0){
                    combv.push_back(5);
                }
                else{
                    combv.push_back(4);
                }
            }
        }
        if(length==10){
            for(int i=0;i<2;i++){
                combv.push_back(5);
            }
        }
        if(length==11){
            for(int i=0;i<3;i++){
                if(i==0){
                    combv.push_back(3);
                }
                else{
                    combv.push_back(4);
                }
        }
        }
        if(length==13){
            for(int i=0;i<4;i++){
                if(i==0){
                   combv.push_back(4);
                }
                else{
                    combv.push_back(3);
                }
            }
        }
        /*if(length==13){
            for(int i=0;i<3;i++){
                if(i==0){
                    combv.push_back(5);
                }
                else{
                    combv.push_back(4);
                }
            }
        }*/
        
        /*if(length==15){
            for(int i=0;i<4;i++){
                if(i==0){
                    combv.push_back(3);
                }
                else{
                    combv.push_back(4);
                }
            }
        }*/
        if(length==15){
            for(int i=0;i<3;i++){
               
                    combv.push_back(5);
                
            }
        }
        
        
        std::cout<<"combv: ";
        for(int i =0;i<combv.size();i++){
            std::cout<<combv[i]<<" ";
        }
        
        for (int i = 0; i < num; i++) {
            elements.push_back(i);
        }
        
        
        
        for (int i = 0; i < length; i++) {
            guess.push_back(0); //????
            pos.push_back(0);  //????
            position.push_back(i);
            invert_position.push_back(14-i);
        }
        
        //        combination(length, 0, current, elements);
        //        generatePool();
    }
    
    
    
    
    void create_attempt2(std::vector<int>& attempt){
        
        attempt = guess;
        if(check_white_process&&count == 0){
            
            for (int i = 0; i < combv[order_combv]; i++) {
                if (i < combv[order_combv]) {
                    attempt[i]=i;
                }
            }
            count=100;
            guess=attempt;
            
            for(int i =0;i<length;i++){
                std::cout<<attempt[i];
            }
            
        }
        
        
        for(int i =0;i<length;i++){
            std::cout<<attempt[i];}
        if(need_pool){
            new_pool=true;
        }
    }
    
    
    void learn2(std::vector<int>& attempt, int black_hits, int white_hits) {
        if (black_hits > black) {
            posn++;
            black++;
        }
        guess[posn]++;
    }
    
    void create_attempt3(std::vector<int>& attempt){
        attempt = pos;
    }
    
    
    void learn3(std::vector<int>& attempt, int black_hits, int white_hits) {
        attempts++;
        std::cout<<"attempts"<<attempts<<std::endl;
        if(check_white_process==false){
            
            
            if(white_hits==0){
                if(black_hits==0){
                    no_white=count_w_n;
                    std::cout<<"no white"<<no_white<<std::endl;
                    check_white_process=true;
                    black=0;  count=0;
                    guess.clear();
                    for(int n=0;n<length;n++){
                        guess.push_back(no_white);
                    }
                }
                else{count_w_n++;
                    guess.clear();
                    for(int n=0;n<length;n++){
                        guess.push_back(count_w_n);
                    }
                }
            }
            
        }
        
        if(count>0){
            
            black_hits=black_hits-black;
            
            if(black_hits==combv[order_combv]){
                std::cout<<"extra_black"<<black_hits<<std::endl;
                std::cout<<"extra_white"<<white_hits<<std::endl;
                nextstart = nextstart+combv[order_combv];
                std::cout<<"next start"<<nextstart;
                order_combv++;
                if(order_combv<combv.size()){
                    for (int i = 0; i < combv[order_combv]; i++) {
                    if (i < combv[order_combv]) {
                        guess[i+nextstart]=i;
                }
                }
                }
                
                if(combv[order_combv]==combv[order_combv-1]){
                    pool = copy_pool;
                    new_pool = false;
                }
                else{
                    need_pool=true;
                    copy_pool.clear();
                    pool.clear();
                }
                black = black+combv[order_combv-1];
                std::cout<<"  BLACK  :"<<black<<std::endl;
            }
            
            
            
            else{
                if(new_pool){
                    for (int i = 0; i < combv[order_combv]; i++) {
                        current.push_back(0);
                    }
                    combination(combv[order_combv], 0, current, elements);
                    copy_pool =pool;
                    std::cout<<"size of pool :"<<pool.size()<<std::endl;
                    new_pool=false;
                }
                
                std::vector< std::vector<int> > newPool;
                small_attempt.clear();
                for(int i =0;i<combv[order_combv];i++){
                    small_attempt.push_back(guess[i+nextstart]);
                }
                std::cout<<std::endl;
                std::cout<<"S a: ";
                for(int i =0;i<small_attempt.size();i++){
                    std::cout<<small_attempt[i];
                }
                
                for (int i = 0; i < pool.size(); i++) {
                    int b = 0, w = 0;
                    give_feedback2(pool[i],small_attempt,b,w);
                    if (b == black_hits ) {
                        newPool.push_back(pool[i]);
                    }
                    
                }
                
                
                pool = newPool;
                small_attempt = pool[0];
                for(int i =0;i<combv[order_combv];i++){
                    guess[i+nextstart]=small_attempt[i];
                }
                
                
            }
            
        }
        
    }
    
    
    
    
    
    
    
    void combination(int combinationLength, int position, std::vector<int> &current, std::vector<int> &elements) {
        
        if (position >= combinationLength) {
            pool.push_back(current);
            return;
        }
        
        for (int j = 0; j < elements.size(); ++j) {
            current[position] = elements[j];
            combination(combinationLength, position + 1, current, elements);
        }
        return;
    }
    
    void generatePool () {
        int pos = length-1;
        for (int i = 0; i < std::pow(num, length); i++) {
            pool.push_back(current);
            current[pos]++;
            for (int i = length-1; i > 0; i--) {
                if (current[i] == num) {
                    current[i] = 0;
                    current[i-1]++;
                }
            }
        }
    }
    
    void give_feedback(const std::vector<int>& attempt, const std::vector<int>& sequence, int& black_hits, int& white_hits){
        std::vector<int> timesSequence, timesAttempt;
        int total_hits = 0;
        for (int i = 0; i < num; i++) {
            timesSequence.push_back(0);
            timesAttempt.push_back(0);
        }
        
        for (int i = 0; i < length; i++) {
            if (attempt[i] == sequence[i]) {
                black_hits++;
            }
            
            timesSequence[sequence[i]]++;
            timesAttempt[attempt[i]]++;
        }
        
        for (int i = 0; i < num; i++) {
            total_hits += std::min(timesSequence[i],timesAttempt[i]);
        }
        
        white_hits = total_hits - black_hits;
    }
    void give_feedback2(const std::vector<int>& attempt, const std::vector<int>& sequence, int& black_hits, int& white_hits){
        std::vector<int> timesSequence, timesAttempt;
        int total_hits = 0;
        for (int i = 0; i < num; i++) {
            timesSequence.push_back(0);
            timesAttempt.push_back(0);
        }
        
        for (int i = 0; i < combv[order_combv]; i++) {
            if (attempt[i] == sequence[i]) {
                black_hits++;
            }
            
            timesSequence[sequence[i]]++;
            timesAttempt[attempt[i]]++;
        }
        
        for (int i = 0; i < num; i++) {
            total_hits += std::min(timesSequence[i],timesAttempt[i]);
        }
        
        white_hits = total_hits - black_hits;
    }
    std::vector<int> current;
    std::vector<int> elements;
    std::vector< std::vector<int> > pool;
    std::vector< std::vector<int> > copy_pool;
    std::vector<int> guess;
    std::vector<int> pos;
    std::vector<int> gua;
    
    int length;
    int num;
    int black;
    int posn;
    int po;
    int count;
    bool determine;
    int next_element;
    int count_b_n;
    int totalblack;
    int totalwhite;
    int previous_element_of_posn;
    int previous_element_of_po;
    int stage;
    bool check_white_process;
    int count_w;
    int count_w_n;
    bool totalwhite_taken;
    int no_white;
    int count_w_pre_n;
    bool be_processed;

    std::vector<int>position;
    std::vector<int>invert_position;
    int black2;
    std::vector<int>pre_attempt;
    int attempts;
    int comb;
    std::vector<int> combv;
    std::vector<int> range;
    int white;
    int order_combv;
    bool new_pool;
    std::vector<int> small_attempt;
    bool need_pool;
    int initial_length;
    int nextstart;
    
};
int main(){
    
    set_random_seed();
    
    int length = 15, num = 6;
    //    std::cout << "enter length of sequence and number of possible values:" << std::endl;
    //    std::cin >> length >> num;
    mm_solver solver;
    solver.init(length, num);
    
    mm_code_maker maker;
    maker.init(length, num);
    maker.generate_sequence();
    int black_hits=0, white_hits=0;
    int attempts_limit = 200;
    int attempts = 0;
    
    std::cout << "the sequence generated by the code maker was:" << std::endl;
    for(int i = 0; i < maker.sequence.size(); i++){
        std::cout << maker.sequence[i] << " ";
    }
    
    while((black_hits < length) && (attempts < attempts_limit)){
        std::vector<int> attempt;
        solver.create_attempt2(attempt);
        maker.give_feedback(attempt, black_hits, white_hits);
        std::cout << "attempt: " << std::endl;
        
        for(int i = 0; i < attempt.size(); i++){
            std::cout << attempt[i] << " ";
        }
        
        std::cout << std::endl;
        std::cout << "black pegs: " << black_hits << " " << " white pegs: " << white_hits << std::endl;
        std::cout << "Remaining Pool: " << solver.pool.size() << std::endl;
        solver.learn3(attempt, black_hits, white_hits);
        attempts++;
    }
    if(black_hits == length){
        std::cout << "the solver has found the sequence in " << attempts << " attempts" << std::endl;
    }
    else{
        std::cout << "after " << attempts << " attempts still no solution" << std::endl;
    }
    std::cout << "the sequence generated by the code maker was:" << std::endl;
    for(int i = 0; i < maker.sequence.size(); i++){
        std::cout << maker.sequence[i] << " ";
    }
    std::cout << std::endl << std::endl << std::endl;
    
    std::vector<int> la, ha;
    solver.create_attempt3(la);
    
    print(la);
    
    int last = 0;
    
    for (int i = 0; i < la.size(); i++) {
        
        
    }
    
    std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
    return 0;
    
    
}
void set_random_seed(){
    std::srand(std::time(0));
}

int randn(int n){
    return std::rand() % n;
}

void print(std::vector<int> ha) {
    for (int i = 0; i < ha.size(); i++) {
        std::cout << ha[i] << " ";
    }
    std::cout << std::endl;
}








