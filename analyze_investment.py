#!/usr/bin/env python3
"""
Investment Behavior Analysis Script

This script analyzes the output from the C++ investment test program
and creates visualizations of how investment decisions change with capacity.
"""

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os
import sys

def load_and_analyze_data(csv_file="investment_analysis.csv"):
    """Load the CSV data from the C++ test program"""
    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found. Run the C++ test program first.")
        return None
        
    df = pd.read_csv(csv_file)
    print("Data loaded successfully!")
    print(f"Shape: {df.shape}")
    print("\nColumn summary:")
    print(df.describe())
    
    return df

def create_investment_plots(df):
    """Create various plots analyzing investment behavior"""
    
    # Set up the plotting style
    plt.style.use('seaborn-v0_8')
    fig = plt.figure(figsize=(15, 12))
    
    # Plot 1: Desired Investment vs Capacity
    plt.subplot(2, 3, 1)
    for capital in df['Capital'].unique():
        subset = df[df['Capital'] == capital]
        plt.plot(subset['Capacity'], subset['Desired_Investment'], 
                marker='o', label=f'Capital: {capital:,.0f}')
    plt.xlabel('Capacity')
    plt.ylabel('Desired Investment (items)')
    plt.title('Investment Demand vs Capacity')
    plt.legend()
    plt.grid(True)
    
    # Plot 2: Expected Cashflow vs Capacity  
    plt.subplot(2, 3, 2)
    for capital in df['Capital'].unique():
        subset = df[df['Capital'] == capital]
        plt.plot(subset['Capacity'], subset['Expected_Cashflow'], 
                marker='s', label=f'Capital: {capital:,.0f}')
    plt.xlabel('Capacity')
    plt.ylabel('Expected Cashflow')
    plt.title('Investment Cashflow vs Capacity')
    plt.legend()
    plt.grid(True)
    
    # Plot 3: NPV vs Capacity
    plt.subplot(2, 3, 3)
    for capital in df['Capital'].unique():
        subset = df[df['Capital'] == capital]
        plt.plot(subset['Capacity'], subset['NPV_Estimate'], 
                marker='^', label=f'Capital: {capital:,.0f}')
    plt.xlabel('Capacity')
    plt.ylabel('NPV Estimate')
    plt.title('Net Present Value vs Capacity')
    plt.legend()
    plt.grid(True)
    plt.axhline(y=0, color='r', linestyle='--', alpha=0.7)
    
    # Plot 4: Investment Efficiency (Investment per unit capacity)
    plt.subplot(2, 3, 4)
    df['Investment_Efficiency'] = df['Desired_Investment'] / df['Capacity']
    for capital in df['Capital'].unique():
        subset = df[df['Capital'] == capital]
        plt.plot(subset['Capacity'], subset['Investment_Efficiency'], 
                marker='d', label=f'Capital: {capital:,.0f}')
    plt.xlabel('Capacity') 
    plt.ylabel('Investment per Unit Capacity')
    plt.title('Investment Efficiency vs Capacity')
    plt.legend()
    plt.grid(True)
    
    # Plot 5: Cashflow ROI (Cashflow per investment)
    plt.subplot(2, 3, 5)
    # Avoid division by zero
    df['Cashflow_ROI'] = np.where(df['Desired_Investment'] > 0, 
                                 df['Expected_Cashflow'] / df['Desired_Investment'], 0)
    for capital in df['Capital'].unique():
        subset = df[df['Capital'] == capital]
        plt.plot(subset['Capacity'], subset['Cashflow_ROI'], 
                marker='p', label=f'Capital: {capital:,.0f}')
    plt.xlabel('Capacity')
    plt.ylabel('Cashflow per Investment Unit')
    plt.title('Investment ROI vs Capacity')
    plt.legend()
    plt.grid(True)
    
    # Plot 6: 3D Surface plot of NPV vs Capacity and Capital
    ax = plt.subplot(2, 3, 6, projection='3d')
    
    # Create meshgrid for 3D plot
    capacities = df['Capacity'].unique()
    capitals = df['Capital'].unique() 
    
    X, Y = np.meshgrid(capacities, capitals)
    Z = np.zeros_like(X)
    
    for i, cap in enumerate(capacities):
        for j, capital in enumerate(capitals):
            npv_val = df[(df['Capacity'] == cap) & (df['Capital'] == capital)]['NPV_Estimate'].values
            if len(npv_val) > 0:
                Z[j, i] = npv_val[0]
    
    surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8)
    ax.set_xlabel('Capacity')
    ax.set_ylabel('Capital')
    ax.set_zlabel('NPV Estimate')
    ax.set_title('NPV Surface: Capacity vs Capital')
    
    plt.tight_layout()
    plt.savefig('investment_analysis_plots.png', dpi=300, bbox_inches='tight')
    plt.show()

def create_summary_report(df):
    """Generate a summary report of key insights"""
    
    print("\n" + "="*60)
    print("INVESTMENT BEHAVIOR ANALYSIS REPORT")
    print("="*60)
    
    # Key statistics
    print(f"\nCapacity Range Tested: {df['Capacity'].min():,.0f} - {df['Capacity'].max():,.0f}")
    print(f"Capital Levels Tested: {', '.join([f'{x:,.0f}' for x in sorted(df['Capital'].unique())])}")
    
    # Investment patterns
    max_investment = df.loc[df['Desired_Investment'].idxmax()]
    print(f"\nHighest Investment Demand:")
    print(f"  Capacity: {max_investment['Capacity']:,.0f}")
    print(f"  Capital: {max_investment['Capital']:,.0f}")
    print(f"  Investment: {max_investment['Desired_Investment']:,.0f} items")
    
    # Cashflow analysis
    max_cashflow = df.loc[df['Expected_Cashflow'].idxmax()]
    print(f"\nBest Expected Cashflow:")
    print(f"  Capacity: {max_cashflow['Capacity']:,.0f}")
    print(f"  Capital: {max_cashflow['Capital']:,.0f}")
    print(f"  Cashflow: {max_cashflow['Expected_Cashflow']:,.2f}")
    
    # NPV analysis
    best_npv = df.loc[df['NPV_Estimate'].idxmax()]
    print(f"\nBest NPV:")
    print(f"  Capacity: {best_npv['Capacity']:,.0f}")
    print(f"  Capital: {best_npv['Capital']:,.0f}")
    print(f"  NPV: {best_npv['NPV_Estimate']:,.2f}")
    
    # Capacity scaling insights
    print(f"\nCapacity Scaling Analysis:")
    for capital in sorted(df['Capital'].unique()):
        subset = df[df['Capital'] == capital].sort_values('Capacity')
        investment_growth = subset['Desired_Investment'].iloc[-1] / subset['Desired_Investment'].iloc[0]
        capacity_growth = subset['Capacity'].iloc[-1] / subset['Capacity'].iloc[0]
        print(f"  Capital {capital:,.0f}: Investment scales {investment_growth:.2f}x vs {capacity_growth:.1f}x capacity")

def main():
    """Main analysis function"""
    print("Investment Behavior Analysis")
    print("="*40)
    
    # Load data
    df = load_and_analyze_data()
    if df is None:
        return
        
    # Create plots
    print("\nGenerating plots...")
    create_investment_plots(df)
    
    # Generate report
    create_summary_report(df)
    
    print(f"\nAnalysis complete! Plots saved as 'investment_analysis_plots.png'")

if __name__ == "__main__":
    main()