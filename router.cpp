#include "router.h"
#include <iomanip>
#include <sstream>

Router::Router(SearchEngine *search, Cart *cart) {
    // TODO: Complete the constructor implementation
    this->search = search;
    this->cart = cart;
}

std::string Router::handle(std::string path) {
    // TODO: Complete the handle function
    std::string response;
    if (path.find("/cart/add/") == 0){
        int id = std::stoi(path.substr(10));
        cart->add_item(id);
        response = "Added item " + std::to_string(id) + "\n";
    } else if (path == "/cart") {
        auto items = cart->list_items();
        for (auto &p : items)
            response += p.to_string() + "\n";
    } else if (path == "/cart/clear") {
        cart->clear();
        response = "Cleared cart\n";
    } else if (path == "/cart/checkout") {
        int total_cents = cart->calculate_checkout_total();
        double total_dollars = total_cents / 100.0;
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << total_dollars;
        response = "Your total is: $" + oss.str() + "\n";
    } else if (path.find("/search") == 0){
        std::string query = "";
            int min_price = -1;
            int max_price = -1;

            auto pos = path.find('?');
            if (pos != std::string::npos) {
                std::string params = path.substr(pos + 1);
                std::istringstream iss(params);
                std::string token;

                while (std::getline(iss, token, '&')) {
                    auto eq = token.find('=');
                    if (eq != std::string::npos) {
                        std::string key = token.substr(0, eq);
                        std::string val = token.substr(eq + 1);

                        if (key == "query") {
                            query = val;
                        } else if (key == "min_price") {
                            min_price = std::stoi(val);
                        } else if (key == "max_price") {
                            max_price = std::stoi(val);
                        }
                    }
                }
            }

            
            auto results = search->query(query, min_price, max_price);
            for (auto &p : results) {
                response += p.to_string() + "\n";
            }
    }
    return response;
}
