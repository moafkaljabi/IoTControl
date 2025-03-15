"use client"; // Required for using useState and event handlers

import { useState } from "react";

export default function DashboardPage() {
  const [data, setData] = useState<string | null>(null); // Store fetched data

  const fetchData = async () => {
    try {
      const response = await fetch("http://localhost:4000/Account/1"); // Adjust URL if needed
      const result = await response.json(); // Parse JSON response
  
      console.log("Fetched result:", result); // Log the full result for inspection
  
      // Check the structure and extract the relevant information to display
      if (result) {
        // Display relevant fields from the response, e.g., firstName and lastName
        const accountDetails = `Name: ${result.firstName} ${result.lastName}, Balance: ${result.balance}`;
        setData(accountDetails); // Set data to display
      } else {
        setData("No data available.");
      }
    } catch (error) {
      console.error("Error fetching data:", error);
      setData("Failed to fetch data");
    }
  };
  

  return (
    <div className="flex flex-col items-center justify-center h-screen">
      <h1 className="text-2xl font-bold mb-4">Dashboard</h1>
      
      <button 
        onClick={fetchData} 
        className="px-6 py-3 bg-green-500 text-white rounded-lg hover:bg-green-600 transition"
      >
        Fetch Data from Backend
      </button>

      {/* ✅ Display fetched data here */}
      {data && (
        <p className="mt-4 p-4 bg-gray-100 border rounded-lg text-lg text-gray-700">
          {data}
        </p>
      )}
    </div>
  );
}
