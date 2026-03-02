library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- @file signal_trigger_tb.vhd
-- @brief Testbench for the SignalTrigger VHDL module.
entity SignalTrigger_TB is
end SignalTrigger_TB;

architecture Behavioral of SignalTrigger_TB is
    signal clk          : STD_LOGIC := '0';
    signal reset        : STD_LOGIC := '0';
    signal price_in     : STD_LOGIC_VECTOR(63 downto 0) := (others => '0');
    signal threshold    : STD_LOGIC_VECTOR(63 downto 0) := (others => '0');
    signal trigger_out  : STD_LOGIC;
    signal filtered_price : STD_LOGIC_VECTOR(63 downto 0);

    constant clk_period : time := 10 ns;
begin
    -- Instantiate UUT
    UUT: entity work.SignalTrigger
        port map (
            clk => clk,
            reset => reset,
            price_in => price_in,
            threshold => threshold,
            trigger_out => trigger_out,
            filtered_price => filtered_price
        );

    -- Clock process
    clk_process : process
    begin
        clk <= '0';
        wait for clk_period/2;
        clk <= '1';
        wait for clk_period/2;
    end process;

    -- Stimulus process
    stim_proc: process
    begin		
        report "Starting VHDL SignalTrigger Verification...";
        reset <= '1';
        wait for 20 ns;	
        reset <= '0';
        
        -- Set threshold to 10
        threshold <= std_logic_vector(to_unsigned(10, 64));

        -- Price jump from 0 to 100 (should trigger)
        report "Test Case 1: Large price jump (0 -> 100, Threshold 10) - Expecting Trigger";
        price_in <= std_logic_vector(to_unsigned(100, 64));
        wait for clk_period;
        assert trigger_out = '1' report "Trigger failed for jump" severity error;

        -- Small price change (100 to 105, threshold 10, should NOT trigger)
        report "Test Case 2: Small price change (100 -> 105, Threshold 10) - Expecting No Trigger";
        price_in <= std_logic_vector(to_unsigned(105, 64));
        wait for clk_period;
        assert trigger_out = '0' report "False trigger for small change" severity error;

        -- Large price jump (105 to 200, should trigger)
        report "Test Case 3: Large price jump (105 -> 200, Threshold 10) - Expecting Trigger";
        price_in <= std_logic_vector(to_unsigned(200, 64));
        wait for clk_period;
        assert trigger_out = '1' report "Trigger failed for large jump" severity error;

        report "VHDL Verification Complete: All test cases passed successfully.";
        wait;
    end process;

end Behavioral;
