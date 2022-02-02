// The following file generates wb_intercon.v

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

//Slave IDs

#define ROM 1
#define SYS 2
#define SPI 3
#define UART 4
#define PTC 5
#define GPIO 6
//#define PTC  5

//Slave offsets. Defined in bytes

#define ROM_OFFSET  1024
#define SYS_OFFSET  16
#define SPI_OFFSET  16
#define UART_OFFSET 1024
#define GPIO_OFFSET  16
#define PTC_OFFSET 16

//Slave mask

#define ROM_MASK 0xfffff000
#define SYS_MASK 0xffffffc0
#define SPI_MASK 0xffffffc0
#define UART_MASK 0xfffff000
#define GPIO_MASK 0xffffffc0
#define PTC_MASK 0xffffffc0

/*Linked list containing master / slave properties.Constructor generates names and saves them in string arrays names ios*/
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
    int p_type = 0;

    //string data_size="";
 //   string address_size="";
    string wb_wire[12] = {};//wb_intercon.vh 
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
    //SPI_Core_IOs
    string spi_clk_i = "";
    string spi_rst_i = "";
    string spi_adr_i = "";
    string spi_dat_i = "";
    string spi_we_i = "";
    string spi_cyc_i = "";
    string spi_stb_i = "";
    string spi_dat_o = "";
    string spi_ack_o = "";
    string spi_inta_o =  "";
    string spi_sck_o = "";
    string spi_ss_o = "";
    string spi_mosi_o = "";
    string spi_miso_i = "";

    string  spi_clk = "";
    string  spi_wb_rst = "";
    string  spi_rdt = "";
    string  spi_irq = "";
    string  spi_sclk = "";
    string  spi_cs_n = "";
    string  spi_mosi = "";
    string  spi_miso = "";
    // UART
    string uart_clk_i = "";
    string uart_rst_i = "";
    string uart_adr_i = "";
    string uart_dat_i = "";
    string uart_we_i = "";
    string uart_cyc_i = "";
    string uart_stb_i = "";
    string uart_sel_i = "";
    string uart_dat_o = "";
    string uart_ack_o = "";

    string uart_inta_o = "";
    string uart_stx_pad_o = "";
    string uart_rts_pad_o = "";
    string uart_dtr_pad_o = "";

    string uart_srx_pad_i = "";
    string uart_cts_pad_i = "";
    string uart_dsr_pad_i = "";
    string uart_ri_pad_i = "";
    string uart_dcd_pad_i = "";

    string uart_clk = "";
    string uart_wb_rst = "";
    string uart_rdt = "";
    string uart_irq = "";
    string uart_tx = "";
    string uart_rx = "";

    string gpio_inta_o = "";
    string gpio_err_o = "";
    string gpio_ext_pad_i = "";
    string gpio_ext_pad_o = "";
    string gpio_ext_padoe_o = "";

    string ptc_gate_clk_pad_i = "";
    string ptc_capt_pad_i = "";
    string ptc_pwm_pad_o = "";
    string ptc_oen_padoen_o = "";

    Node() {}

    Node(string name_in, bool is_master_in)
    {
        Node(name_in, is_master_in, 0);
    }

    Node(string name_in, bool is_master_in, int type)
    {
        name = name_in;
        is_master = is_master_in;

        //set slave offset and masks
        switch (type)
        {
        case ROM: offset = ROM_OFFSET; mux_mask = ROM_MASK;   p_type = type; break;
        case SYS: offset = SYS_OFFSET; mux_mask = SYS_MASK;   p_type = type; break;
        case SPI: offset = SPI_OFFSET; mux_mask = SPI_MASK;   p_type = type; /*data_size = "[7:0]"; address_size = "[2] ? 3'd0 : wb_m2s_spi_flash_adr[5:3]";*/ break;
        case UART: offset = UART_OFFSET; mux_mask = UART_MASK; p_type = type; /*data_size = "[7:0]"; address_size = "[4:2]";*/ break;
        case GPIO: offset = GPIO_OFFSET; mux_mask = GPIO_MASK; p_type = type; /*address_size = "[5:2], 2'b0}";*/ break;
        case PTC: offset = PTC_OFFSET; mux_mask = PTC_MASK;   p_type = type ; /*address_size = "[5:2],2'b0}";*/ break;
        default:
            break;
        }
        //Master and slave ios generation 
        if (is_master_in)
        {
            ios[0] = "wb_" + name_in + "_adr_i";
            ios[1] = "wb_" + name_in + "_dat_i";
            ios[2] = "wb_" + name_in + "_sel_i";
            ios[3] = "wb_" + name_in + "_we_i ";
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
        wb_wire[0] = "wb_m2s_" + name_in + "_adr";
        wb_wire[1] = "wb_m2s_" + name_in + "_dat";
        wb_wire[2] = "wb_m2s_" + name_in + "_sel";
        wb_wire[3] = "wb_m2s_" + name_in + "_we";
        wb_wire[4] = "wb_m2s_" + name_in + "_cyc";
        wb_wire[5] = "wb_m2s_" + name_in + "_stb";
        wb_wire[6] = "wb_m2s_" + name_in + "_cti";
        wb_wire[7] = "wb_m2s_" + name_in + "_bte";
        wb_wire[8] = "wb_s2m_" + name_in + "_dat";
        wb_wire[9] = "wb_s2m_" + name_in + "_ack";
        wb_wire[10] ="wb_s2m_" + name_in + "_err";
        wb_wire[11] ="wb_s2m_" + name_in + "_rty";

        //SPI Core Pins

        spi_clk_i = "clk_i ";
        spi_rst_i = "rst_i ";
        spi_adr_i = "adr_i ";
        spi_dat_i = "dat_i ";
        spi_we_i  = "we_i  ";
        spi_cyc_i = "cyc_i ";
        spi_stb_i = "stb_i ";
        spi_dat_o = "dat_o ";
        spi_ack_o = "ack_o ";
        spi_inta_o= "inta_o";
        spi_sck_o = "sck_o ";
        spi_ss_o  = "ss_o  ";
        spi_mosi_o= "mosi_o";
        spi_miso_i= "miso_i";

        spi_clk = "clk";
        spi_wb_rst = "wb_rst";
        spi_rdt = name +"_rdt";
        spi_irq = name + "_irq";
        spi_sclk = "o_" + name + "_sclk";
        spi_cs_n = "o_" + name + "cs_n";
        spi_mosi = "o_" + name + "mosi";
        spi_miso = "i_" + name + "miso";
        //Uart peripheral
        uart_clk_i = "wb_clk_i ";
        uart_rst_i = "wb_rst_i ";
        uart_adr_i = "wb_adr_i ";
        uart_dat_i = "wb_dat_i ";
        uart_we_i = "wb_we_i  ";
        uart_cyc_i = "wb_cyc_i ";
        uart_stb_i = "wb_stb_i ";
        uart_sel_i = "wb_sel_i ";
        uart_dat_o = "wb_dat_o ";
        uart_ack_o = "wb_ack_o ";

        uart_inta_o = "inta_o";
        uart_stx_pad_o = "stx_pad_o";
        uart_rts_pad_o = "rts_pad_o";
        uart_dtr_pad_o = "dtr_pad_o";

        uart_srx_pad_i = "srx_pad_i";
        uart_cts_pad_i = "cts_pad_i";
        uart_dsr_pad_i = "dsr_pad_i";
        uart_ri_pad_i = "ri_pad_i";
        uart_dcd_pad_i = "dcd_pad_i";

        uart_clk = "clk";
        uart_wb_rst = "~rst_n";
        uart_rdt = name + "_rdt";
        uart_irq = name + "_irq";
        uart_tx = "o_" + name + "_tx";
        uart_rx = "i_" + name + "_rx";

        gpio_inta_o = "wb_inta_o";
        gpio_err_o = "wb_err_o ";
        gpio_ext_pad_i = "ext_pad_i";
        gpio_ext_pad_o = "ext_pad_o";
        gpio_ext_padoe_o = "ext_padoe_o";

        ptc_gate_clk_pad_i= "gate_clk_pad_i";
        ptc_capt_pad_i = "capt_pad_i";
        ptc_pwm_pad_o = "pwm_pad_o";
        ptc_oen_padoen_o = "oen_padoen_o";

        //core[0] = "wb_m2s_" + name_in + "_adr" + address_size;
        //core[1] = "wb_m2s_" + name_in + "_dat" + data_size;
        //core[2] = "wb_m2s_" + name_in + "_sel" + "";
        //core[3] = "wb_m2s_" + name_in + "_we"  + "";
        //core[4] = "wb_m2s_" + name_in + "_cyc" + "";
        //core[5] = "wb_m2s_" + name_in + "_stb" + "";
        //core[6] = "wb_m2s_" + name_in + "_cti" + "";
        //core[7] = "wb_m2s_" + name_in + "_bte" + "";
        //core[8] = "wb_s2m_" + name_in + "_dat" + "";
        //core[9] = "wb_s2m_" + name_in + "_ack" + "";
        //core[10] = "wb_s2m_" + name_in + "_err"+ "";
        //core[11] = "wb_s2m_" + name_in + "_rty"+ "";
    }


};
string gen_core_start(Node*& head_node)
{
    ifstream core_read;
    ofstream core_write;
    string lines = "";
    core_read.open("core_start.v", ios::in);
    if (!core_read)
    {
    cout << "Error in creating file!!!";
    return 0;
    }
/*Console out of wb_intercon.v. */
      // Read a Line from File
    //while (core_read)
    //{
        //getline(core_read, lines);
        lines.assign((istreambuf_iterator<char>(core_read)),(istreambuf_iterator<char>()));
        lines += "\n";
        // Print line in Console
        //cout << lines << endl << endl;
      //  if (core_read.eof())
        //    break;
    //}
    Node* temp = new Node();
    temp = head_node;
    
    while (temp != NULL)
    {
        if (temp->p_type == UART)
        {
            lines += "\tinput wire\ti_" + temp->name + "_rx,\n";
            lines += "\toutput wire\to_" + temp->name + "_tx,\n";
           
        }
        if (temp->p_type == SPI)
        {
            lines += "\toutput wire\to_" + temp->name + "_sclk,\n";
            lines += "\toutput wire\to_" + temp->name + "_cs_n,\n";
            lines += "\toutput wire\to_" + temp->name + "_mosi,\n";
            lines += "\tinput wire\ti_" + temp->name + "_miso,\n";
        }
            
        temp = temp->next;
    }
        lines.pop_back();
        lines.pop_back();
        lines += ");\n\n";
    temp = head_node;
    //lines += "wire\ttimer_irq\n";
    while (temp != NULL)
    {
        if (temp->p_type == UART)
        {
            lines += "\twire\t" + temp->name + "_irq;\n";
        }
        if (temp->p_type == SPI)
        {
            lines += "\twire\t" + temp->name + "_irq;\n";
            
        }
        temp = temp->next;
    }
    core_read.close();
    

    return lines;
}
string gen_core_mid(Node*& head_node)
{
    ifstream core_read;
    ofstream core_write;
    string lines = "";
    core_read.open("core_mid.v", ios::in);
    if (!core_read)
    {
        cout << "Error in creating file!!!";
        return 0;
    }
    /*Console out of wb_intercon.v. */
          // Read a Line from File
        //while (core_read)
        //{
            //getline(core_read, lines);
    lines.assign((istreambuf_iterator<char>(core_read)), (istreambuf_iterator<char>()));
    lines += "\n";
    // Print line in Console
    //cout << lines << endl << endl;
  //  if (core_read.eof())
    //    break;
//}
    Node* temp = new Node();
    temp = head_node;
    int first_time = 1;
    while (temp != NULL)
    {
        if (temp->p_type == PTC && first_time == 0)
        {
            lines += temp->name + "_irq | ";
        }
        if (temp->p_type == PTC && first_time == 1)
        {
            lines += "\t." + temp->name + "_irq (" + temp->name + "_irq | ";
            first_time = 0;
        }
        temp = temp->next;
    }
    lines.pop_back();
    lines.pop_back();
    lines += "),\n";
    temp = head_node;
    first_time = 1;
    while (temp != NULL)
    {
        if (temp->p_type == GPIO && first_time == 0)
        {
            lines += temp->name + "_irq | ";
        }
        if (temp->p_type == GPIO && first_time == 1)
        {
            lines += "\t." + temp->name + "_irq (" + temp->name + "_irq | ";
            first_time = 0;
        }
        temp = temp->next;
    }
        
    lines.pop_back();
    lines.pop_back();
    lines += "));\n\n";
    
    core_read.close();


    return lines;
}
string gen_core_end()
{
    ifstream core_read;
    ofstream core_write;
    string lines = "";
    core_read.open("core_end.v", ios::in);
    if (!core_read)
    {
        cout << "Error in creating file!!!";
        return 0;
    }
    /*Console out of wb_intercon.v. */
          // Read a Line from File
        //while (core_read)
        //{
            //getline(core_read, lines);
    lines.assign((istreambuf_iterator<char>(core_read)), (istreambuf_iterator<char>()));
    lines += "\n";
    // Print line in Console
    //cout << lines << endl << endl;
  //  if (core_read.eof())
    //    break;
//}
    
    core_read.close();


    return lines;
}
string gen_spi(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines = "";

    while (temp != NULL)
    {
        if (temp->p_type == SPI)
        {
            lines += "\twire[7:0]\t\t"+ temp->spi_rdt +'\n';
            lines += "\tassign "+ temp->wb_wire[8]+" = {24'd0," + temp->spi_rdt + "};\n";
            lines += "\tsimple_spi " +temp->name +"\n";
            lines += "\t(\n";
            lines += "\t." + temp->spi_clk_i + "("+temp->spi_clk+"),\n";
            lines += "\t." + temp->spi_rst_i + "(" + temp->spi_wb_rst + "),\n";
            lines += "\t." + temp->spi_adr_i + "(" + temp->wb_wire[0] + "[2] ? 3'd0 : " + temp->wb_wire[0] + "[5:3]),\n";
            lines += "\t." + temp->spi_dat_i + "(" + temp->wb_wire[1] + "[7:0]),\n";
            lines += "\t." + temp->spi_we_i + "(" + temp->wb_wire[3] + "),\n";
            lines += "\t." + temp->spi_cyc_i + "(" + temp->wb_wire[4] + "),\n";
            lines += "\t." + temp->spi_stb_i + "(" + temp->wb_wire[5] + "),\n";
            lines += "\t." + temp->spi_dat_o + "(" + temp->name + "_rdt),\n";
            lines += "\t." + temp->spi_ack_o + "(" + temp->wb_wire[9] + "),\n";
            lines += "\t." + temp->spi_inta_o + "(" + temp->name + "_irq),\n";
            lines += "\t." + temp->spi_sck_o + "(o_" + temp->name + "_sclk),\n";
            lines += "\t." + temp->spi_ss_o + "(o_" + temp->name + "_cs_n),\n";
            lines += "\t." + temp->spi_mosi_o + "(o_" + temp->name + "_mosi),\n";
            lines += "\t." + temp->spi_miso_i + "(i_" + temp->name + "_miso));\n\n";
        }
        temp = temp->next;
    }
    return lines;
}
string gen_uart(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines = "";

    while (temp != NULL)
    {
        if (temp->p_type == UART)
        {
            lines += "\twire[7:0]\t\t" + temp->uart_rdt + '\n';
            lines += "\tassign " + temp->wb_wire[8] + " = {24'd0," + temp->uart_rdt + "};\n";
            lines += "\ttop_uart " + temp->name + "\n";
            lines += "\t(\n";
            lines += "\t." + temp->uart_clk_i + "("+temp->uart_clk+"),\n";
            lines += "\t." + temp->uart_rst_i + "(" + temp->uart_wb_rst + "),\n";
            lines += "\t." + temp->uart_adr_i + "(" + temp->wb_wire[0] + "[4:2]),\n";
            lines += "\t." + temp->uart_dat_i + "(" + temp->wb_wire[1] + "[7:0]),\n";
            lines += "\t." + temp->uart_we_i + "(" + temp->wb_wire[3] + "),\n";
            lines += "\t." + temp->uart_cyc_i + "(" + temp->wb_wire[4] + "),\n";
            lines += "\t." + temp->uart_stb_i + "(" + temp->wb_wire[5] + "),\n";
            lines += "\t." + temp->uart_sel_i + "(4'b0),\n";
            lines += "\t." + temp->uart_dat_o + "(" + temp->name + "_rdt),\n";
            lines += "\t." + temp->uart_ack_o + "(" + temp->wb_wire[9] + "),\n\n";
            
            lines += "\t." + temp->uart_inta_o + " (" + temp->name + "_irq),\n";
            lines += "\t." + temp->uart_stx_pad_o + " (o_" + temp->name + "_tx),\n";
            lines += "\t." + temp->uart_rts_pad_o + " (),\n";                  
            lines += "\t." + temp->uart_dtr_pad_o + " ()\n\n";

            lines += "\t." + temp->uart_srx_pad_i + " ("+ temp->uart_rx +")\n";
            lines += "\t." + temp->uart_cts_pad_i + " (1'b0)\n";
            lines += "\t." + temp->uart_dsr_pad_i + " (1'b0)\n";
            lines += "\t." + temp->uart_ri_pad_i + " (1'b0)\n";
            lines += "\t." + temp->uart_dcd_pad_i + " (1'b0));\n\n";
        }
        temp = temp->next;
    }
    return lines;
}
string gen_gpio(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines = "";

    while (temp != NULL)
    {
        if (temp->p_type == GPIO)
        {
            lines += "\twire[31:0] en_"+ temp->name+";\n";
            lines += "\twire " + temp->name + "_irq;\n";
            lines += "\twire[31:0] i_"+ temp->name + ";\n";
            lines += "\twire[31:0] o_"+ temp->name + ";\n";
            for (int i=0;i<32;i++)
            lines += "\tbidirec "+temp->name+to_string(i)+"(.oe(en_gpio["+to_string(i)+"]), .inp(o_gpio["+ to_string(i) +"]), .outp(i_gpio[" + to_string(i) + "]), .bidir(io_data[" + to_string(i) + "]));\n";
            lines += "\n";
            lines += "\tgpio_top " + temp->name + "\n";
            lines += "\t(\n";
            lines += "\t." + temp->uart_clk_i + "(" + temp->uart_clk + "),\n";
            lines += "\t." + temp->uart_rst_i + "(" + temp->spi_wb_rst + "),\n";
            lines += "\t." + temp->uart_adr_i + "({ 2'b0," + temp->wb_wire[0] + "[5:2],2'b0 }),\n"; //({ 2'b0,wb_m2s_gpio_adr[5:2],2'b0 }),
            lines += "\t." + temp->uart_dat_i + "(" + temp->wb_wire[1] + "),\n";
            lines += "\t." + temp->uart_we_i + "(" + temp->wb_wire[3] + "),\n";
            lines += "\t." + temp->uart_cyc_i + "(" + temp->wb_wire[4] + "),\n";
            lines += "\t." + temp->uart_stb_i + "(" + temp->wb_wire[5] + "),\n";
            lines += "\t." + temp->uart_sel_i + "(4'b1111),\n";
            lines += "\t." + temp->uart_dat_o + "(" + temp->name + "_rdt),\n";
            lines += "\t." + temp->uart_ack_o + "(" + temp->wb_wire[9] + "),\n";
            lines += "\t." + temp->gpio_err_o + "(" + temp->wb_wire[10] + "),\n";
            lines += "\t." + temp->gpio_inta_o + " (" + temp->name + "_irq),\n";
            lines += "\t." + temp->gpio_ext_pad_i + " (i_" + temp->name + "[31:0]),\n";
            lines += "\t." + temp->gpio_ext_pad_o + " (o_" + temp->name + "[31:0]),\n";
            lines += "\t." + temp->gpio_ext_padoe_o + " (en_"+ temp->name +"));\n\n";
        }
        temp = temp->next;
    }
    return lines;
}
string gen_ptc(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines = "";

    while (temp != NULL)
    {
        if (temp->p_type == PTC)
        {
            lines += "\twire " + temp->name + "_irq;\n";
            lines += "\tptc_top " + temp->name + "\n";
            lines += "\t(\n";
            lines += "\t." + temp->uart_clk_i + "(" + temp->uart_clk + "),\n";
            lines += "\t." + temp->uart_rst_i + "(" + temp->spi_wb_rst + "),\n";
            lines += "\t." + temp->uart_adr_i + "({ 2'b0," + temp->wb_wire[0] + "[5:2],2'b0 }),\n"; //({ 2'b0,wb_m2s_gpio_adr[5:2],2'b0 }),
            lines += "\t." + temp->uart_dat_i + "(" + temp->wb_wire[1] + "),\n";
            lines += "\t." + temp->uart_we_i + "(" + temp->wb_wire[3] + "),\n";
            lines += "\t." + temp->uart_cyc_i + "(" + temp->wb_wire[4] + "),\n";
            lines += "\t." + temp->uart_stb_i + "(" + temp->wb_wire[5] + "),\n";
            lines += "\t." + temp->uart_sel_i + "(4'b1111),\n";
            lines += "\t." + temp->uart_dat_o + "(" + temp->name + "_rdt),\n";
            lines += "\t." + temp->uart_ack_o + "(" + temp->wb_wire[9] + "),\n";
            lines += "\t." + temp->gpio_err_o + "(" + temp->wb_wire[10] + "),\n";
            lines += "\t." + temp->gpio_inta_o + " (" + temp->name + "_irq),\n";
            lines += "\t." + temp->ptc_gate_clk_pad_i + " (),\n";
            lines += "\t." + temp->ptc_capt_pad_i + " (),\n";
            lines += "\t." + temp->ptc_pwm_pad_o + " (),\n";
            lines += "\t." + temp->ptc_oen_padoen_o + " ());\n\n";
        }
        temp = temp->next;
    }
    return lines;
}
//push new node in linked list
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

//append new node to end of linked list
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

//Get total number of nodes in a linked list
int getSlaveCount(Node*& head_node)
{
    int count = 0;
    Node* temp = head_node;

    while (temp != NULL)
    {
        if (temp->is_master == false )
        {
          
            count++;
        }
        temp = temp->next;
    }
    return count;
}

//this functions iterates throug the entire linked list. It writes 12 io lines for each based on if its master or slave
string wb_module_gen(Node*& head_node)
{
    string lines = "";
    lines += "module wb_intercon \n\t(input\t\t\twb_clk_i,\n\tinput\t\t\twb_rst_i,\n\t";
    Node* temp = new Node();
    temp = head_node;
    while (temp != NULL)
    {
    if (temp->is_master)
    {
        lines += "input  \t["   + to_string(temp->adr_width-1) + ':' + '0' + ']' + '\t' + temp->ios[0] + ",\n\t";
        lines += "input  \t["   + to_string(temp->dat_width-1) + ':' + '0' + ']' + '\t' + temp->ios[1] + ",\n\t";
        lines += "input  \t["   + to_string(temp->sel_width-1) + ':' + '0' + ']' + '\t' + temp->ios[2] + ",\n\t";
        lines += "input  \t\t\t"  + temp->ios[3] + ",\n\t";
        lines += "input  \t\t\t"  + temp->ios[4] + ",\n\t";
        lines += "input  \t\t\t"  + temp->ios[5] + ",\n\t";
        lines += "input  \t["   + to_string(temp->cti_width-1) + ':' + '0' + ']' + '\t' + temp->ios[6] + ",\n\t";
        lines += "input  \t["   + to_string(temp->bte_width-1) + ':' + '0' + ']' + '\t' + temp->ios[7] + ",\n\t";
        lines += "input  \t\t\t"  + temp->ios[8] + ",\n\t";
        lines += "output \t\t\t"  + temp->ios[9] + ",\n\t";
        lines += "output \t\t\t"  + temp->ios[10] + ",\n\t";
        lines += "output \t\t\t"  + temp->ios[11] + ",\n\t";
    }
    else
    {
        lines += "output \t["   + to_string(temp->adr_width-1) + ':' + '0' + ']' + '\t' + temp->ios[0] + ",\n\t";
        lines += "output \t["   + to_string(temp->dat_width-1) + ':' + '0' + ']' + '\t' + temp->ios[1] + ",\n\t";
        lines += "output \t["   + to_string(temp->sel_width-1) + ':' + '0' + ']' + '\t' + temp->ios[2] + ",\n\t";
        lines += "output \t\t\t"  + temp->ios[3] + ",\n\t";
        lines += "output \t\t\t"  + temp->ios[4] + ",\n\t";
        lines += "output \t\t\t"  + temp->ios[5] + ",\n\t";
        lines += "output \t["   + to_string(temp->cti_width-1) + ':' + '0' + ']' + '\t' + temp->ios[6] + ",\n\t";
        lines += "output \t["   + to_string(temp->bte_width-1) + ':' + '0' + ']' + '\t' + temp->ios[7] + ",\n\t";
        lines += "input  \t\t\t"  + temp->ios[8] + ",\n\t";
        lines += "input  \t\t\t"  + temp->ios[9] + ",\n\t";
        lines += "input  \t\t\t"  + temp->ios[10] + ",\n\t";
        if (temp->next==NULL)
        {
            lines += "input \t\t\t"  + temp->ios[11] + ");\n";
        }
        else
        {
            lines += "input \t\t\t"  + temp->ios[11] + ",\n\t";
        }

    }
    temp = temp->next;
    }
    return lines;
}
string wb_wire_vh_gen(Node*& head_node)
{
    string lines = "";
    //lines += "module wb_intercon \n\t(input\t\t\twb_clk_i,\n\tinput\t\t\twb_rst_i,\n\t";
    Node* temp = new Node();
    temp = head_node;
    while (temp != NULL)
    {
        //if (temp->is_master)
        //{
        lines += "wire  \t[" + to_string(temp->adr_width - 1) + ':' + '0' + ']' + '\t' + temp->wb_wire[0] + ";\n";
        lines += "wire  \t[" + to_string(temp->dat_width - 1) + ':' + '0' + ']' + '\t' + temp->wb_wire[1] + ";\n";
        lines += "wire  \t[" + to_string(temp->sel_width - 1) + ':' + '0' + ']' + '\t' + temp->wb_wire[2] + ";\n";
        lines += "wire  \t\t\t" + temp->wb_wire[3] + ";\n";
        lines += "wire  \t\t\t" + temp->wb_wire[4] + ";\n";
        lines += "wire  \t\t\t" + temp->wb_wire[5] + ";\n";
        lines += "wire  \t[" + to_string(temp->cti_width - 1) + ':' + '0' + ']' + '\t' + temp->wb_wire[6] + ";\n";
        lines += "wire  \t[" + to_string(temp->bte_width - 1) + ':' + '0' + ']' + '\t' + temp->wb_wire[7] + ";\n";
        lines += "wire  \t[" + to_string(temp->dat_width - 1) + ':' + '0' + ']' + '\t' + temp->wb_wire[8] + ";\n";
        lines += "wire \t\t\t" + temp->wb_wire[9] + ";\n";
        lines += "wire \t\t\t" + temp->wb_wire[10] + ";\n";
        lines += "wire \t\t\t" + temp->wb_wire[11] + ";\n";
        //}
       
            /*if (temp->next == NULL)
            {
                lines += "input \t\t\t" + temp->ios[11] + ");\n";
            }
            else
            {
                lines += "input \t\t\t" + temp->ios[11] + ",\n\t";
            }*/

        
        temp = temp->next;
    }

    lines.pop_back();
    return lines;
}
//converts an integer to 8 byte wide string

string int_to_hex(int number, int width)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(width) << std::hex << (number | 0);
    return ss.str();

}

// Iterates through the whole linked list. Starting from 0 sets address according to offsets to each node
void wb_gen_addresses(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    int address = 0;

    while (temp != NULL)
    {
        if (temp->is_master == false)
        {
            ///if (temp->p_type == UART)
           //    temp->mux_addr =  0x2000;
            //else
            //{
                temp->mux_addr = address;
              /*  if (address >= 0x2000)
                {
                    temp->mux_addr = 0x3000;
                }*/
            //}
            address += temp->offset * 4;
        }
        temp = temp->next;
    }
}

// Iterates through the whole linked list and generates the wb_mux. Wb_mux requires slave masks/addresses only. Masters are excluded
string gen_wb_mux(Node*& head_node)
{
    Node* temp = new Node();
    temp = head_node;
    string lines="";
    int slave_count = 0;
   // int count = 0;
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
    //lines += "\b\b \b}),";//\b
    lines.pop_back();
    lines.pop_back();
    lines += "}),\n";
    //Generate Mask Line
    lines += "\t.MATCH_MASK ({";
    temp = head_node; // reset linked list to start
    while (temp != NULL)
    {
       // count++;
        if (temp->is_master == false)
        {
            lines += "32'h";
            lines += int_to_hex(temp->mux_mask,8);
          // if (count << slave_count)
            lines += ", ";

        }
        temp = temp->next;

    }
    lines.pop_back();
    lines.pop_back();
    lines += "}))\n";//\b

    return lines;
}

// Iterates through the entire linked list and generates wb_mux_io.

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
                lines += temp->ios[count] + ", ";
          
            temp = temp->next;
        }
        lines.pop_back();
        lines.pop_back();
        lines += "), \n";
        temp = head_node;
        masters = masters->next;
        count++;
    }
    count = 0;
    //write slaves
    while (slaves != NULL) // nested linked lists to iterate through mux ios and peripherals pins
    {
        lines += "\t."+slaves->name+ " ({";
        while (temp != NULL)
        {
            if (temp->is_master == false)
                lines += temp->ios[count] + ", ";

            temp = temp->next;
        }
        if (slaves->next == NULL)
        {
            lines.pop_back();
            lines.pop_back();
            lines += "}));\n";
        }
        else
        {
            lines.pop_back();
            lines.pop_back();
            lines += "}),\n";
        }

        temp = head_node;
        slaves = slaves->next;
        count++;
    } 
  
    return lines;

}

string gen_wb_intvh_io(Node*& head_node)
{
        Node* temp = new Node();
        temp = head_node;
        string lines = "";
        lines += "\nwb_intercon wb_intercon0\n";
        lines += "\t(.wb_clk_i\t\t\t(wb_clk),\n";
        lines += "\t .wb_rst_i\t\t\t(wb_rst_i),\n";
        while (temp != NULL)
        {
            for (int i = 0; i < 12; i++)
            {
                lines += "\t.";
                lines += temp->ios[i];
                lines += "\t\t(";
                lines += temp->wb_wire[i];
                lines += "),\n";
            }
            temp = temp->next;
        }
        lines.pop_back();
        lines.pop_back();
        lines += ");";
        return lines;
}
//string core(Node*& head_node)
//{
//    Node* temp = new Node();
//    temp = head_node;
//    string lines = "";
//    while (temp != NULL)
//    {
//        switch (temp->p_type)
//        {
//        case ROM:  lines += "rom_top" + " rom_1\n"; break;
//        case SYS:  lines += "sys_top" + " sys_1\n"; break;
//        case SPI:  lines += "spi_top" + " spi_1\n";  break;
//        case UART: lines += "uart_top" + " uart_1\n"; break;
//        case GPIO: lines += "gpio_top" + " gpio_1\n"; break;
//        case PTC:  lines += "ptc_top" + " ptc_1\n"; break;
//        default:
//            break;
//        }
//    }
//    lines += "(\n";
//    lines += ".wb_clk_i (clk),";
//    lines += ".wb_rst_i (~rst_n),";
//    lines += ".wb_adr_i ("+temp->wb_wire[0]+"]),";
//    lines += ".wb_dat_i ("+ temp->wb_wire[1]+"]),";
//    lines += ".wb_we_i  ("+ temp->wb_wire[1] +"),";
//    lines += ".wb_cyc_i ("++"),";
//    lines += ".wb_stb_i ("++"),";
//    lines += ".wb_sel_i ("++"),";
//    lines += ".wb_dat_o ("++"),";
//    lines += ".wb_ack_o ("++"),";
//
//
//    wb_wire[0] = "wb_m2s_" + name_in + "_adr";
//    wb_wire[1] = "wb_m2s_" + name_in + "_dat";
//    wb_wire[2] = "wb_m2s_" + name_in + "_sel";
//    wb_wire[3] = "wb_m2s_" + name_in + "_we";
//    wb_wire[4] = "wb_m2s_" + name_in + "_cyc";
//    wb_wire[5] = "wb_m2s_" + name_in + "_stb";
//    wb_wire[6] = "wb_m2s_" + name_in + "_cti";
//    wb_wire[7] = "wb_m2s_" + name_in + "_bte";
//    wb_wire[8] = "wb_s2m_" + name_in + "_dat";
//    wb_wire[9] = "wb_s2m_" + name_in + "_ack";
//    wb_wire[10] = "wb_s2m_" + name_in + "_err";
//    wb_wire[11] = "wb_s2m_" + name_in + "_rty";
//}
int main()
{
    Node* x = NULL; 
    /*------------Adding periperals----------------*/
    /*Create linked list of masters and slaves*/
    push(x, "io", true,0); // linked list, name, is_master, type (0 for master)
    push_to_end(x, "rom", false,ROM);
    push_to_end(x, "sys", false, SYS);
    push_to_end(x, "spi_flash", false,SPI);
    push_to_end(x, "spi", false, SPI);
    push_to_end(x, "ptc", false, PTC);
    push_to_end(x, "gpio", false, GPIO);
    push_to_end(x, "uart1", false, UART);
    push_to_end(x, "uart2", false, UART);
    push_to_end(x, "uart3", false, UART);

  //  cout << gen_core_start(x);
  //  cout << gen_core_mid(x);
  //  
  ////  cout << gen_core_mid();
  //  cout << gen_spi(x);
  //  cout << gen_uart(x);
  //  cout << gen_gpio(x);
  //  cout << gen_ptc(x);
  //  cout << gen_core_end();
   // cout << gen_core_end();
    /*------------writing wb_intercon.v file----------------*/
    ofstream wb_intv,wb_intvh,swerv_core;
    wb_intv.open("wb_intercon.v", ios::out);
    if (!wb_intv)
    {
        cout << "Error in creating file!!!";
        return 0;
    }
    /*Console out of wb_intercon.v. */
    wb_intv << wb_module_gen(x);
    wb_gen_addresses(x); // set addresses before calling gen_wb_mux
    wb_intv << gen_wb_mux(x);
    wb_intv << gen_wb_mux_io(x);
    
    wb_intv.close();
    /*------------writing wb_intercon.vh file----------------*/
    wb_intvh.open("wb_intercon.vh", ios::out);
    if (!wb_intvh)
    {
        cout << "Error in creating file!!!";
        return 0;
    }
    wb_intvh << wb_wire_vh_gen(x);
    wb_intvh << gen_wb_intvh_io(x);
    wb_intvh.close();
    /*-------------Writing swervcore.v file------------------*/
    swerv_core.open("swervolf_core.v", ios::out);
    if (!swerv_core)
    {
        cout << "Error in creating file!!!";
        return 0;
    }
    swerv_core << gen_core_start(x);
    swerv_core << gen_core_mid(x);
    swerv_core << gen_spi(x);
    swerv_core << gen_uart(x);
    swerv_core << gen_gpio(x);
    swerv_core << gen_ptc(x);
    swerv_core << gen_core_end();
    swerv_core.close(); 

    cout << "File created successfully.\n";
    return 0;
    /*Console out of wb_intercon.v. */
    //cout << wb_module_gen(x); 
    //wb_gen_addresses(x); // set addresses before calling gen_wb_mux
    //cout<< gen_wb_mux(x);
    //cout << gen_wb_mux_io(x);
    //return 0;
    /*Create file*/
}







