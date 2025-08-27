#include "cart.h"

Cart::Cart(const std::vector<Product> *catalog_ptr) {
    // TODO: Complete the constructor implementation
    this->catalog_ptr = catalog_ptr;
}

void Cart::add_item(int id) {
    // TODO: Complete the add_item function
    items.push_back(id);
}

std::vector<Product> Cart::list_items() {
    // TODO: Complete the list_items function
    std::vector<Product> ans;
    for(size_t i = 0; i < items.size(); i++){
        int id = items[i];
        
        for(size_t j = 0; j < catalog_ptr->size(); j++){
            const Product &p = (*catalog_ptr)[j];
            if(p.id == id){
                ans.push_back(p);
                break;
            }
        }
    }
    return ans;
}

void Cart::clear() {
    // TODO: Complete the clear function
    items.clear();
}

int Cart::calculate_checkout_total() {
    // TODO: Complete the calculate_checkout_total function
    int sub_total = 0;
    for(size_t i = 0; i < items.size(); i++){
        int id = items[i];
        
        for(size_t j = 0; j < catalog_ptr->size(); j++){
            const Product &p = (*catalog_ptr)[j];
            if(p.id == id){
                sub_total += p.price;
                break;
            }
        }
    }
    
    int total = static_cast<int>(sub_total * 1.1);
    
    return total;
}
