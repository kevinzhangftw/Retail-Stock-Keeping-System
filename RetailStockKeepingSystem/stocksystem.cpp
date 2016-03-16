//
//  stocksystem.cpp
//  RetailStockKeepingSystem
//
//  Created by Kevin Zhang on 2016-02-29.
//  Copyright © 2016 Kevin Zhang. All rights reserved.
//

#include "stocksystem.hpp"
// default constructor;
// begin with a balance of $100,000.00
StockSystem::StockSystem(){
    balance = 100000;
}

// returns the balance member
double StockSystem::GetBalance(){
    return balance;
}

// Add a new SKU to the system. Do not allow insertion of duplicate sku
bool StockSystem::StockNewItem(StockItem item){
    if (records.Search(item)) {
        return false;
    }else{
        records.Insert(item);
        return true;
    }
}

// Locate the item with key itemsku and update its description field.
// Return false if itemsku is not found.
bool StockSystem::EditStockItemDescription(int itemsku, string desc){
    //init an stockitem
    StockItem inputItem =  StockItem(itemsku, desc, 0);
    //search this identical item, if it is found return a pointer to it
    StockItem* valueRetreived = records.Retrieve(inputItem);
    //if the pointer is null, must be that retrieve failed
    if (valueRetreived == NULL) {
        return false;
    }else{
        valueRetreived->SetDescription(desc);
        return true;
    }
}

// Locate the item with key itemsku and update its description field.
// Return false if itemsku is not found or retailprice is negative.
bool StockSystem::EditStockItemPrice(int itemsku, double retailprice){
    //init an stockitem
    StockItem inputItem =  StockItem(itemsku, "ignore this message", retailprice);
    //search this identical item, if it is found return a pointer to it
    StockItem* valueRetreived = records.Retrieve(inputItem);
    //if the pointer is null, must be that retrieve failed
    if (valueRetreived == NULL) {
        return false;
    }else{
        //check negative pricing
        if (valueRetreived->GetPrice() < 0) {
            return false;
        }else{
            valueRetreived->SetPrice(retailprice);
            return true;
        }
    }
}

// Purchase quantity of item at unitprice each, to reach a maximum (post-purchase) on-hand stock quantity of 1000.
// Return false if balance is not sufficient to make the purchase,
//   or if SKU does not exist, or if quantity or unitprice are negative.
// Otherwise, return true and increase the item's on-hand stock by quantity,
//   and reduce balance by quantity*unitprice.
bool StockSystem::Restock(int itemsku, int quantity, double unitprice){
    //to reach a maximum (post-purchase) on-hand stock quantity of 1000.
    if (balance < quantity*unitprice) {
        return false;
    }
    StockItem inputItem =  StockItem(itemsku, "ignore this message", unitprice);
    //search this identical item, if it is found return a pointer to it
    StockItem* valueRetreived = records.Retrieve(inputItem);
    //if the pointer is null, must be that retrieve failed
    if (valueRetreived == NULL||quantity<0||(valueRetreived->GetStock()+quantity)>1000||unitprice<0){
        return false;
    }else{
        valueRetreived->SetStock(valueRetreived->GetStock()+quantity);
        balance = balance-(quantity*unitprice);
        return true;
    }
}

// Sell an item to a customer, if quantity of stock is available and SKU exists.
// Reduce stock by quantity, increase balance by quantity*price, and return true if stock available.
// If partial stock (less than quantity) available, sell the available stock and return true.
// If no stock, sku does not exist, or quantity is negative, return false.
bool StockSystem::Sell(int itemsku, int quantity){
    //:TODO
    return false;
}