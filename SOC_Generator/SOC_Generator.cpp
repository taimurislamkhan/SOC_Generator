// SOC_Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node
{
public:
    bool is_master=false;
    string name="";
    Node* next = NULL;

};

void push(Node*& head_node, string name,bool is_master)
{
    Node* new_node = new Node();
    new_node->next = head_node;
    new_node->name = name;
    new_node->is_master = is_master;
    head_node = new_node;

}

void push_to_end(Node*& head_node, string name, bool is_master)
{
    Node* new_node = new Node();
    new_node->next = NULL;
    new_node->name = name;
    new_node->is_master = is_master;
    Node* last = head_node;
    if (head_node == NULL)
    {
        return;
    }
    else
    {
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_node;
    }
}

class peripheral
{
public:
    string module_name;
    int wb_clk = 1;
    int wb_rst = 1;
    int adr_o;
    int dat_o;
    int sel_o;
    int we_o;
    int cyc_o;
    int stb_o;
    int cti_o;
    int bte_o;
    int dat_i;
    int ack_i;
    int err_i;
    int rty_i;

    string n_adr_o;
    string n_dat_o;
    string n_sel_o;
    string n_we_o;
    string n_cyc_o;
    string n_stb_o;
    string n_cti_o;
    string n_bte_o;
    string n_dat_i;
    string n_ack_i;
    string n_err_i;
    string n_rty_i;

     peripheral(string name,bool master)
    {
         module_name = name;
         //Assign pins
         adr_o = 32-1;
         dat_o = 32-1;
         sel_o = 4-1;
         we_o = 1-1;
         cyc_o = 1-1;
         stb_o = 1-1;
         cti_o = 3-1;
         bte_o = 2-1;
         dat_i = 32-1;
         ack_i = 1-1;
         err_i = 1-1;
         rty_i = 1-1;
         //Assign name
         if (master)
         {
             n_adr_o = "wb_" + name + "_adr_i";
             n_dat_o = "wb_" + name + "_dat_i";
             n_sel_o = "wb_" + name + "_sel_i";
             n_we_o  = "wb_" + name + "_we_i";
             n_cyc_o = "wb_" + name + "_cyc_i";
             n_stb_o = "wb_" + name + "_stb_i";
             n_cti_o = "wb_" + name + "_cti_i";
             n_bte_o = "wb_" + name + "_bte_i";
             n_dat_i = "wb_" + name + "_dat_o";
             n_ack_i = "wb_" + name + "_ack_o";
             n_err_i = "wb_" + name + "_err_o";
             n_rty_i = "wb_" + name + "_rty_o";
         }
         else
         {
             n_adr_o = "wb_" + name + "_adr_o";
             n_dat_o = "wb_" + name + "_dat_o";
             n_sel_o = "wb_" + name + "_sel_o";
             n_we_o  = "wb_" + name + "_we_o ";
             n_cyc_o = "wb_" + name + "_cyc_o";
             n_stb_o = "wb_" + name + "_stb_o";
             n_cti_o = "wb_" + name + "_cti_o";
             n_bte_o = "wb_" + name + "_bte_o";
             n_dat_i = "wb_" + name + "_dat_i";
             n_ack_i = "wb_" + name + "_ack_i";
             n_err_i = "wb_" + name + "_err_i";
             n_rty_i = "wb_" + name + "_rty_i";
         }

 

    }

     string IO_generate(bool start,bool master, bool last)
     {
         string io_line="";
         if (start)
         {
             io_line += "module wb_intercon \n\t(input\twb_clk_i,\n\tinput\twb_rst_i,\n\t";
         }

         if (master)
         {
             io_line += "input \t[" + to_string(adr_o) + ':' + '0' + ']' + '\t' + n_adr_o + ",\n\t";
             io_line += "input \t[" + to_string(dat_o) + ':' + '0' + ']' + '\t' + n_dat_o + ",\n\t";
             io_line += "input \t[" + to_string(sel_o) + ':' + '0' + ']' + '\t' + n_sel_o + ",\n\t";
             io_line += "input \t[" + to_string(we_o) + ':' + '0' + ']' + '\t' + n_we_o + ",\n\t";
             io_line += "input \t[" + to_string(cyc_o) + ':' + '0' + ']' + '\t' + n_cyc_o + ",\n\t";
             io_line += "input \t[" + to_string(stb_o) + ':' + '0' + ']' + '\t' + n_stb_o + ",\n\t";
             io_line += "input \t[" + to_string(cti_o) + ':' + '0' + ']' + '\t' + n_cti_o + ",\n\t";
             io_line += "input \t[" + to_string(bte_o) + ':' + '0' + ']' + '\t' + n_bte_o + ",\n\t";
             io_line += "input \t[" + to_string(dat_i) + ':' + '0' + ']' + '\t' + n_dat_i + ",\n\t";
             io_line += "output \t[" + to_string(ack_i) + ':' + '0' + ']' + '\t' + n_ack_i + ",\n\t";
             io_line += "output \t[" + to_string(err_i) + ':' + '0' + ']' + '\t' + n_err_i + ",\n\t";
             io_line += "output \t[" + to_string(rty_i) + ':' + '0' + ']' + '\t' + n_rty_i + ",\n\t";
         }
         else
         {
             io_line += "output \t[" + to_string(adr_o) + ':' + '0' + ']' + '\t' + n_adr_o + ",\n\t";
             io_line += "output \t[" + to_string(dat_o) + ':' + '0' + ']' + '\t' + n_dat_o + ",\n\t";
             io_line += "output \t[" + to_string(sel_o) + ':' + '0' + ']' + '\t' + n_sel_o + ",\n\t";
             io_line += "output \t[" + to_string(we_o) + ':' + '0' + ']' + '\t' + n_we_o + ",\n\t";
             io_line += "output \t[" + to_string(cyc_o) + ':' + '0' + ']' + '\t' + n_cyc_o + ",\n\t";
             io_line += "output \t[" + to_string(stb_o) + ':' + '0' + ']' + '\t' + n_stb_o + ",\n\t";
             io_line += "output \t[" + to_string(cti_o) + ':' + '0' + ']' + '\t' + n_cti_o + ",\n\t";
             io_line += "output \t[" + to_string(bte_o) + ':' + '0' + ']' + '\t' + n_bte_o + ",\n\t";
             io_line += "input \t[" + to_string(dat_i) + ':' + '0' + ']' + '\t' + n_dat_i + ",\n\t";
             io_line += "input \t[" + to_string(ack_i) + ':' + '0' + ']' + '\t' + n_ack_i + ",\n\t";
             io_line += "input \t[" + to_string(err_i) + ':' + '0' + ']' + '\t' + n_err_i + ",\n\t";
             if (last)
             {
                 io_line += "input \t[" + to_string(rty_i) + ':' + '0' + ']' + '\t' + n_rty_i + ");";
             }
             else
             {
                 io_line += "input \t[" + to_string(rty_i) + ':' + '0' + ']' + '\t' + n_rty_i + ",\n\t";
             }

         }

         return io_line;
     }
};

string gen_module(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines;
    int start = 1;
    int last = 0;

    while (temp != NULL)
    {
        if (temp->next == NULL)
        {
            last = true;
        }
        peripheral temp_peripheral = peripheral(temp->name, temp->is_master);
        lines += temp_peripheral.IO_generate(start, temp->is_master, last);
        temp = temp->next;
        start = false;
    }
    return lines;
}

string gen_wb_mux_io(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines;
    Node* slaves = NULL;
    Node* masters = NULL;

    //create masters pin modes list
    push(masters, "_adr_i", false);
    push_to_end(masters, "_dat_i", false);
    push_to_end(masters, "_sel_i", false);
    push_to_end(masters, "_we_i ", false);
    push_to_end(masters, "_cyc_i", false);
    push_to_end(masters, "_stb_i", false);
    push_to_end(masters, "_cti_i", false);
    push_to_end(masters, "_bte_i", false);
    push_to_end(masters, "_dat_o", false);
    push_to_end(masters, "_ack_o", false);
    push_to_end(masters, "_err_o", false);
    push_to_end(masters, "_rty_o", false);

    //create slaves pin modes list
    push(slaves, "_adr_o",false);
    push_to_end(slaves, "_dat_o", false);
    push_to_end(slaves, "_sel_o", false);
    push_to_end(slaves, "_we_o ", false);
    push_to_end(slaves, "_cyc_o", false);
    push_to_end(slaves, "_stb_o", false);
    push_to_end(slaves, "_cti_o", false);
    push_to_end(slaves, "_bte_o", false);
    push_to_end(slaves, "_dat_i", false);
    push_to_end(slaves, "_ack_i", false);
    push_to_end(slaves, "_err_i", false);
    push_to_end(slaves, "_rty_i", false);

    lines += "\nwb_mux_io\n\t(";

    //write master
    lines += ".wb_clk_i  (wb_clk_i),\n\t.wb_rst_i  (wb_rst_i),\n\t";

    while (masters != NULL ) // nested linked lists to iterate through mux ios and peripherals pins
    {
        lines += ".wbm" + masters->name + " (";
        while (temp != NULL && temp->is_master == true)
        {
            lines += "wb_" + temp->name + masters->name;
                lines += "), \n\t";

            temp = temp->next;
        }
        temp = head_node;
        masters = masters->next;
    }

    //write slaves
    while (slaves != NULL) // nested linked lists to iterate through mux ios and peripherals pins
    {
        lines += ".wbs"+slaves->name+ " ({";
        while (temp != NULL)
        {
            lines += "wb_" + temp->name + slaves->name;
            if (temp->next == NULL && slaves->next == NULL) // check if end of module
            {
                break;
            }
   
            if (temp->next == NULL && slaves->next != NULL) // check if end of line
                lines += "}),\n\t";
            else 
                lines += ", ";

            temp = temp->next;
        }
        temp = head_node;
        slaves = slaves->next;
    } 
    lines += "});\n";
    return lines;

}

int main()
{

    Node* x = NULL;
    
    push(x, "io", true);
    push_to_end(x, "rom", false);
    push_to_end(x, "spi_flash", false);
    //push_to_end(x, "sys", false);
    //push_to_end(x, "uart", false);
    //push_to_end(x, "spi", false);
    //push_to_end(x, "i2c", false);
    cout << gen_module(x);
    cout << gen_wb_mux_io(x);


    //peripheral io = peripheral("io", true); // io is name and true for master
    //peripheral spi = peripheral("spi",false);
    //peripheral i2c = peripheral("i2c", false);
    //cout << io.IO_generate(1, true, false);
    //cout << spi.IO_generate(0,false,false); // 0 = not starting line, false = not master , fasle = not last
    //cout << i2c.IO_generate(0, false, true);

}




