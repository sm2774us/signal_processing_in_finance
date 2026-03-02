library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- @file signal_trigger.vhd
-- @brief Silicon-grade FPGA Signal Processor.
-- 
-- This module implements a simple signal trigger based on price jumps.
entity SignalTrigger is
    Port (
        clk           : in  std_logic;
        reset         : in  std_logic; -- Active-high reset to match testbench
        
        -- Inputs
        price_in      : in  std_logic_vector(63 downto 0);
        threshold     : in  std_logic_vector(63 downto 0);
        
        -- Outputs
        trigger_out   : out std_logic;
        filtered_price : out std_logic_vector(63 downto 0)
    );
end SignalTrigger;

architecture Behavioral of SignalTrigger is
    signal last_price : unsigned(63 downto 0) := (others => '0');
begin
    -- Simple trigger logic
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                last_price <= (others => '0');
                trigger_out <= '0';
                filtered_price <= (others => '0');
            else
                -- Check if price jump exceeds threshold
                if abs(signed(unsigned(price_in) - last_price)) >= signed(unsigned(threshold)) then
                    trigger_out <= '1';
                    filtered_price <= price_in;
                    last_price <= unsigned(price_in);
                else
                    trigger_out <= '0';
                    filtered_price <= std_logic_vector(last_price);
                end if;
            end if;
        end if;
    end process;

end Behavioral;
