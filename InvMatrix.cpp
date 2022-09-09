#include<iostream>
#include<vector>

/* Function call for to get Cofactor of Matrix */
void getCofactor(std:: vector< std :: vector <int >> &vec, std:: vector< std :: vector <int >> &temp, int p, int q){
    //std::vector<std::vector<int>> temp(3, std::vector<int>(3));
    int i =0;
    int j = 0;
    for(int row =0; row< vec.size(); row++){
        for (int col = 0; col < vec.size(); col++)
        {
            //copying into temporary matix only those element which are not given row and column
            if(row != p && col != q){
                
                temp[i][j++] = vec[row][col];
            }

            if (j == vec.size() - 1) {
                    j = 0;
                    i++;
            }
        }

    }

}

int determinent (std:: vector< std :: vector <int >> &vec, int n){
    int D = 0; // Initializa the result 
    // Base case: if the matrix contains single element
    if(n==1){
        return vec[0][0];
    }
    std::vector<std::vector<int>> temp(3, std::vector<int>(3));
    int sign = 1;
    for(int f = 0; f<vec.size(); f++){
        //get cofactor of vec[0][f]
        getCofactor(vec, temp, 0,  f);
        D += sign * vec[0][f] * determinent(temp, n-1);

        //terms are to be added with alternate sign
        sign = -sign;
    }
    return D;
}

/* Function Call for Adjoint Matrix */
void adjoint(std:: vector< std :: vector <int >> &vec, std:: vector< std :: vector <int >> &adj){
    //std::vector<std::vector<int>> adj(vec.size(), std::vector<int>(vec.size()));
    if (vec.size() == 1){
        adj[0][0] = 1;
        return;
    }
    std::vector<std::vector<int>> temp(vec.size(), std::vector<int>(vec.size()));
    int sign = 1;
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec.size(); j++){
            //Get Co-factor of the Matrix[i][j]
            getCofactor(vec,temp, i, j);
            //Sign of adj[i][j] positive if sum of row and column indexs is even
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            // Interchanging rows and columns to get the transpose of the cofector Matrix
            adj[j][i] = (sign) * (determinent(temp, vec.size() - 1));
            std:: cout <<adj[j][i]<<" ";
        }
        std::cout<<std::endl;
    }  
}
 
/* Function call for Inverse Matrix */
bool invMatrix(std:: vector< std :: vector <int >> &vec){
    //std::vector<std::vector<int>> det(3, std::vector<int>(3));
    int n = vec.size();
    determinent(vec, n);
    std::cout<<"The Determinent of the Matrix is: "<<determinent(vec,n);
    return true;
}

/* Function call for Matrix Multiplication */
std::vector<std::vector<int>> matMultiply(const std::vector<std::vector<int>> &vec){
    std::vector<std::vector<int>> result(3, std::vector<int>(3));
    for(int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec.size(); j++) {
            for (int k = 0; k < result.size(); k++){
                result[i][j] += vec[i][k] * vec[k][j];
            }
        }   
    }
    return result;
}

/* Display Function */
void display (std::vector<std::vector<int>> vec){
     for(int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec.size(); j++) {
            std :: cout<< vec[i][j]<<" ";
        } 
        std:: cout << std::endl;  
    }
}

int main(){
    
    std :: vector < std :: vector< int > > matrix = {{2,1,3},{6,5,7},{4,9,8}}; // Initilize the vector
    std::vector<std::vector<int>> res(matrix.size(), std::vector<int>(matrix.size())); // Store the result of 2D Matrix Multiplication
    std::vector<std::vector<int>> Ad(matrix.size(), std::vector<int>(matrix.size()));
    std :: cout << "The Given Matrix is: "<<std :: endl;
    display(matrix);
    res = matMultiply(matrix);
    std:: cout <<"Matrix Multiplication is: "<< std :: endl;
    display(res);
    invMatrix(matrix);
    std::cout<<std::endl;
    std::cout<<"The Adjacent Matrix is: "<< std::endl; 
    adjoint(matrix, Ad);
    //display(Ad); 
    return 0;
}