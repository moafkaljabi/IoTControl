
  "use client";
import { useRouter } from "next/navigation";

export default function LoginPage() {
  const router = useRouter();

  const handleLogin = () => {
    // Simulate authentication (can be replaced with real auth logic)
    router.push("/dashboard"); // Navigate to Dashboard
  };

  return (
    <div className="flex flex-col items-center justify-center h-screen">
      <h1 className="text-2xl font-bold mb-4">Login Page</h1>
      <button 
        onClick={handleLogin} 
        className="px-6 py-3 bg-blue-500 text-white rounded-lg hover:bg-blue-600 transition"
      >
        Login
      </button>
    </div>
  );
}
