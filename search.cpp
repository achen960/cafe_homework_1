#include "search.h"

SearchEngine::SearchEngine(const std::vector<Product> *catalog_ptr) {
    // TODO: Complete the constructor implementation
    this->catalog_ptr = catalog_ptr;
}

#include <algorithm>
#include <cctype>

static std::string to_lower(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::vector<Product> SearchEngine::query(std::string query, int min_price, int max_price) {
    // TODO: Complete the query function
    std::vector<Product> ans;
    
    int min_cents = (min_price >= 0) ? min_price * 100 : 0;
    int max_cents = (max_price >= 0) ? max_price * 100 : INT_MAX;
    
    for(size_t i = 0; i < catalog_ptr->size(); i++){
        const Product &p = (*catalog_ptr)[i];
        
        if(to_lower(p.name).find(to_lower(query)) != std::string::npos && p.price >= min_cents && p.price <= max_cents){
            ans.push_back(p);
        }
    }
    return ans;
}
