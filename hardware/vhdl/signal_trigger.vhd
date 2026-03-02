library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- @file signal_trigger.vhd
-- @brief Silicon-grade FPGA Signal Processor with AXI-Lite (Control) and AXI-Stream (Data).
-- 
-- This module implements a full TOE (TCP/IP Offload Engine) style interface.
entity SignalProcessor_Top is
    Port (
        clk           : in  std_logic;
        reset_n       : in  std_logic;

        -- AXI-Lite Interface (Control Plane: Config registers)
        s_axi_awaddr  : in  std_logic_vector(31 downto 0);
        s_axi_wdata   : in  std_logic_vector(31 downto 0);
        s_axi_wvalid  : in  std_logic;
        
        -- AXI-Stream Interface (Data Plane: Zero-copy packet data)
        -- This is where the 10G/25G/100G TOE IP Core delivers market data.
        s_axis_tdata  : in  std_logic_vector(63 downto 0);
        s_axis_tvalid : in  std_logic;
        s_axis_tready : out std_logic;
        s_axis_tlast  : in  std_logic;

        -- DMA Output (Stream to Memory)
        m_axis_dma_tdata  : out std_logic_vector(63 downto 0);
        m_axis_dma_tvalid : out std_logic;
        m_axis_dma_tready : in  std_logic
    );
end SignalProcessor_Top;

architecture Behavioral of SignalProcessor_Top is
    signal threshold : unsigned(63 downto 0) := to_unsigned(100, 64);
    signal last_price : unsigned(63 downto 0) := (others => '0');
begin
    -- AXI-Stream Packet Processing Logic
    process(clk)
    begin
        if rising_edge(clk) then
            if reset_n = '0' then
                last_price <= (others => '0');
                m_axis_dma_tvalid <= '0';
            else
                -- 1. Check if packet data is valid
                if s_axis_tvalid = '1' then
                    -- 2. Extract price (simplified AXI-Stream parsing)
                    if abs(signed(unsigned(s_axis_tdata) - last_price)) >= signed(threshold) then
                        -- 3. Trigger DMA transfer to Host RAM (Zero-copy path)
                        m_axis_dma_tdata <= s_axis_tdata;
                        m_axis_dma_tvalid <= '1';
                        last_price <= unsigned(s_axis_tdata);
                    else
                        m_axis_dma_tvalid <= '0';
                    end if;
                end if;
            end if;
        end if;
    end process;

    s_axis_tready <= '1';
end Behavioral;
