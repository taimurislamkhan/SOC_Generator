// SOC_Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#define ROM 1
#define SYS 2
#define SPI 3
#define UART 4

#define ROM_OFFSET  1024
#define SYS_OFFSET  16
#define SPI_OFFSET  16
#define UART_OFFSET 1024

#define ROM_MASK 0xfffff000
#define SYS_MASK 0xffffffc0
#define SPI_MASK 0xffffffc0
#define UART_MASK 0xfffff000

class Node
{
public:
    bool is_master=false;
    string name="";
    Node* next = NULL;
    int adr_width =    32;
    int dat_width =    32;
    int sel_width  =    4;
    int cti_width  =    3;
    int bte_width  =    2;
    int mux_addr   =    0;
    unsigned int mux_mask   =    0;
    int offset     =    0;

    string ios[12] = {};
    //0 n_adr_o
    //1 n_dat_o
    //2 n_sel_o
    //3 n_we_o
    //4 n_cyc_o
    //5 n_stb_o
    //6 n_cti_o
    //7 n_bte_o
    //8 n_dat_i
    //9 n_ack_i
    //10  n_err_i
    //11  n_rty_i

    Node() {}

    Node(string name_in, bool is_master_in)
    {
        Node(name_in, is_master_in, 0);
    }

    Node(string name_in, bool is_master_in, int type)
    {
        name = name_in;
        is_master = is_master_in;

        switch (type)
        {
        case ROM: offset = ROM_OFFSET; mux_mask = ROM_MASK; break;
        case SYS: offset = SYS_OFFSET; mux_mask = SYS_MASK; break;
        case SPI: offset = SPI_OFFSET; mux_mask = SPI_MASK; break;
        case UART: offset = UART_OFFSET; mux_mask = UART_MASK; break;
        default:
            break;
        }

        if (is_master_in)
        {
            ios[0] = "wb_" + name_in + "_adr_i";
            ios[1] = "wb_" + name_in + "_dat_i";
            ios[2] = "wb_" + name_in + "_sel_i";
            ios[3] = "wb_" + name_in + "_we_i";
            ios[4] = "wb_" + name_in + "_cyc_i";
            ios[5] = "wb_" + name_in + "_stb_i";
            ios[6] = "wb_" + name_in + "_cti_i";
            ios[7] = "wb_" + name_in + "_bte_i";
            ios[8] = "wb_" + name_in + "_dat_o";
            ios[9] = "wb_" + name_in + "_ack_o";
            ios[10] = "wb_" + name_in + "_err_o";
            ios[11] = "wb_" + name_in + "_rty_o";
        }
        else
        {
            ios[0] = "wb_" + name_in + "_adr_o";
            ios[1] = "wb_" + name_in + "_dat_o";
            ios[2] = "wb_" + name_in + "_sel_o";
            ios[3] = "wb_" + name_in + "_we_o ";
            ios[4] = "wb_" + name_in + "_cyc_o";
            ios[5] = "wb_" + name_in + "_stb_o";
            ios[6] = "wb_" + name_in + "_cti_o";
            ios[7] = "wb_" + name_in + "_bte_o";
            ios[8] = "wb_" + name_in + "_dat_i";
            ios[9] = "wb_" + name_in + "_ack_i";
            ios[10] = "wb_" + name_in + "_err_i";
            ios[11] = "wb_" + name_in + "_rty_i";
        }
    }

};

void push(Node*& head_node, string name,bool is_master,int type)
{
    Node* new_node = new Node(name,is_master,type);
    new_node->next = head_node;
    head_node = new_node;

}
void push(Node*& head_node, string name, bool is_master)
{
    push(head_node, name, is_master, 0);
}

void push_to_end(Node*& head_node, string name, bool is_master,int type)
{
    Node* new_node = new Node(name,is_master,type);
    new_node->next = NULL;
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

void push_to_end(Node*& head_node, string name, bool is_master)
{
    push_to_end(head_node, name, is_master, 0);
}

int getSlaveCount(Node*& head_node)
{
    int count = 0;
    Node* temp = head_node;

    while (temp != NULL)
    {
        if (temp->is_master == false)
        {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

string wb_module_gen(Node*& head_node)
{
    string lines = "";
    lines += "module wb_intercon \n\t(input\twb_clk_i,\n\tinput\twb_rst_i,\n\t";
    Node* temp = new Node();
    temp = head_node;
    while (temp != NULL)
    {
    if (temp->is_master)
    {
        lines += "input  \t["   + to_string(temp->adr_width-1) + ':' + '0' + ']' + '\t' + temp->ios[0] + ",\n\t";
        lines += "input  \t["   + to_string(temp->dat_width-1) + ':' + '0' + ']' + '\t' + temp->ios[1] + ",\n\t";
        lines += "input  \t["   + to_string(temp->sel_width-1) + ':' + '0' + ']' + '\t' + temp->ios[2] + ",\n\t";
        lines += "input  \t\t"  + temp->ios[3] + ",\n\t";
        lines += "input  \t\t"  + temp->ios[4] + ",\n\t";
        lines += "input  \t\t"  + temp->ios[5] + ",\n\t";
        lines += "input  \t["   + to_string(temp->cti_width-1) + ':' + '0' + ']' + '\t' + temp->ios[6] + ",\n\t";
        lines += "input  \t["   + to_string(temp->bte_width-1) + ':' + '0' + ']' + '\t' + temp->ios[7] + ",\n\t";
        lines += "input  \t\t"  + temp->ios[8] + ",\n\t";
        lines += "output \t\t"  + temp->ios[9] + ",\n\t";
        lines += "output \t\t"  + temp->ios[10] + ",\n\t";
        lines += "output \t\t"  + temp->ios[11] + ",\n\t";
    }
    else
    {
        lines += "output \t["   + to_string(temp->adr_width-1) + ':' + '0' + ']' + '\t' + temp->ios[0] + ",\n\t";
        lines += "output \t["   + to_string(temp->dat_width-1) + ':' + '0' + ']' + '\t' + temp->ios[1] + ",\n\t";
        lines += "output \t["   + to_string(temp->sel_width-1) + ':' + '0' + ']' + '\t' + temp->ios[2] + ",\n\t";
        lines += "output \t\t"  + temp->ios[3] + ",\n\t";
        lines += "output \t\t"  + temp->ios[4] + ",\n\t";
        lines += "output \t\t"  + temp->ios[5] + ",\n\t";
        lines += "output \t["   + to_string(temp->cti_width-1) + ':' + '0' + ']' + '\t' + temp->ios[6] + ",\n\t";
        lines += "output \t["   + to_string(temp->bte_width-1) + ':' + '0' + ']' + '\t' + temp->ios[7] + ",\n\t";
        lines += "input  \t\t"  + temp->ios[8] + ",\n\t";
        lines += "input  \t\t"  + temp->ios[9] + ",\n\t";
        lines += "input  \t\t"  + temp->ios[10] + ",\n\t";
        if (temp->next==NULL)
        {
            lines += "input \t\t"  + temp->ios[11] + ");\n";
        }
        else
        {
            lines += "input \t\t"  + temp->ios[11] + ",\n\t";
        }

    }
    temp = temp->next;
    }
    return lines;
}

string int_to_hex(int number, int width)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(width) << std::hex << (number | 0);
    return ss.str();

}
string gen_wb_mux(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines="";
    int slave_count = 0;
    slave_count = getSlaveCount(temp);
    lines += "wb_mux\n\t #(.num_slaves (" + to_string(slave_count)+"),\n";
    lines += "\t.MATCH_ADDR ({";
    //lines += "32'h00000000, ";

    //Generate Address Lines
    while (temp!= NULL)
    {
        if (temp->is_master == false)
        {
            lines += "32'h";
            lines += int_to_hex(temp->mux_addr, 8);

            lines += ", ";

            
        }
        temp = temp->next;
        
    }
    lines += "\b\b}),\n";

    //Generate Mask Line
    lines += "\t.MATCH_MASK ({";
    temp = head_node; // reset linked list to start
    while (temp != NULL)
    {
        if (temp->is_master == false)
        {
            lines += "32'h";
            lines += int_to_hex(temp->mux_mask,8);
            lines += ", ";
  

        }
        temp = temp->next;

    }
    lines += "\b\b})\n";

    return lines;
}

string gen_wb_mux_io(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines="";
    Node* slaves = NULL;
    Node* masters = NULL;
    int count = 0;

    //create masters pin modes list
    push       (masters, "wbm_adr_i", false);
    push_to_end(masters, "wbm_dat_i", false);
    push_to_end(masters, "wbm_sel_i", false);
    push_to_end(masters, "wbm_we_i ", false);
    push_to_end(masters, "wbm_cyc_i", false);
    push_to_end(masters, "wbm_stb_i", false);
    push_to_end(masters, "wbm_cti_i", false);
    push_to_end(masters, "wbm_bte_i", false);
    push_to_end(masters, "wbm_dat_o", false);
    push_to_end(masters, "wbm_ack_o", false);
    push_to_end(masters, "wbm_err_o", false);
    push_to_end(masters, "wbm_rty_o", false);

    //create slaves pin modes list
    push       (slaves, "wbs_adr_o",false);
    push_to_end(slaves, "wbs_dat_o", false);
    push_to_end(slaves, "wbs_sel_o", false);
    push_to_end(slaves, "wbs_we_o ", false);
    push_to_end(slaves, "wbs_cyc_o", false);
    push_to_end(slaves, "wbs_stb_o", false);
    push_to_end(slaves, "wbs_cti_o", false);
    push_to_end(slaves, "wbs_bte_o", false);
    push_to_end(slaves, "wbs_dat_i", false);
    push_to_end(slaves, "wbs_ack_i", false);
    push_to_end(slaves, "wbs_err_i", false);
    push_to_end(slaves, "wbs_rty_i", false);

    lines += "\nwb_mux_io\n(";

    //write master
    lines += "\t.wb_clk_i  (wb_clk_i),\n\t.wb_rst_i  (wb_rst_i),\n";

    while (masters != NULL ) // nested linked lists to iterate through mux ios and peripherals pins
    {
        lines += "\t." + masters->name + " (";
        while (temp != NULL)
        {
            if (temp->is_master == true)
                lines += temp->ios[count] + ',';
          
            temp = temp->next;
        }
        lines += "\b), \n";
        temp = head_node;
        masters = masters->next;
    }
    count = 0;
    //write slaves
    while (slaves != NULL) // nested linked lists to iterate through mux ios and peripherals pins
    {
        lines += "\t."+slaves->name+ " ({";
        while (temp != NULL)
        {
            if (temp->is_master == false)
                lines += temp->ios[count] + ',';

            temp = temp->next;
        }
        if (slaves->next == NULL)
            lines += "}));\n";
        else
        lines += "\b}),\n";

        temp = head_node;
        slaves = slaves->next;
        count++;
    } 
  
    return lines;

}


void wb_gen_addresses(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    int address = 0;

    while (temp != NULL)
    {
        if (temp->is_master == false)
        {
            temp->mux_addr = address;
            //cout <<hex<< temp->mux_addr << endl;
            //cout << int_to_hex(temp->mux_addr, 8) << endl;
            address += temp->offset * 4;
        }
        temp = temp->next;
    }
}


int main()
{
    Node* x = NULL; 
    push(x, "io", true,0);
    push_to_end(x, "rom", false,ROM);
    push_to_end(x, "sys", false, SYS);
    push_to_end(x, "spi_flash", false,SPI);
    push_to_end(x, "uart", false, UART);

   cout << wb_module_gen(x);
   wb_gen_addresses(x);
   cout<< gen_wb_mux(x);
   cout << gen_wb_mux_io(x);
}




