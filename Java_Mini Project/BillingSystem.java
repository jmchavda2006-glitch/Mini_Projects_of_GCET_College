import java.io.*;
import java.util.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
public class BillingSystem {
    static class Product {
        int id;
        String name;
        double price;
        int quantity;
        Product(int id, String name, double price, int quantity) {
            this.id = id;
            this.name = name;
            this.price = price;
            this.quantity = quantity;
        }
    }
    static List<Product> inventory = new ArrayList<>();
    static Map<String, String> credentials = new HashMap<>();
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        loadCredentials();
        if (!login()) {
            System.out.println("Exiting system...");
            return;
        }
        loadProductsFromFile();
        int choice;
        do {
            System.out.println("1. Add Product");
            System.out.println("2. Edit Product");
            System.out.println("3. Delete Product");
            System.out.println("4. View All Products");
            System.out.println("5. Generate Bill");
            System.out.println("6. Exit");
            System.out.print("Enter your choice: ");
            choice = scanner.nextInt();
            switch (choice) {
                case 1 -> addProduct(scanner);
                case 2 -> editProduct(scanner);
                case 3 -> deleteProduct(scanner);
                case 4 -> viewAllProducts();
                case 5 -> generateBill(scanner);
                case 6 -> System.out.println("Exiting... Thank you!");
                default -> System.out.println("Invalid choice! Try again.");
            }
        } while (choice != 6);
    }
    public static void loadCredentials() {
        try (BufferedReader br = new BufferedReader(new FileReader("login.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length == 2) {
                    credentials.put(parts[0].trim(), parts[1].trim());
                }
            }
        } catch (IOException e) {
            System.out.println("Error loading login credentials: " + e.getMessage());
        }
    }
    public static boolean login() {
        Scanner scanner = new Scanner(System.in);
        Console console = System.console();
        System.out.println("=========== Automated Billing Management System ===========");
        System.out.print("Enter Admin Username: ");
        String username = scanner.nextLine();
        String password;
        if (console != null) {
            char[] passwordChars = console.readPassword("Enter Admin Password: ");
            password = new String(passwordChars);
        } else {
            System.out.print("Enter Admin Password: ");
            password = scanner.nextLine(); // fallback in IDE
        }
        if (credentials.containsKey(username) && credentials.get(username).equals(password)) {
            System.out.println("Login Successful!\n");
            return true;
        } else {
            System.out.println("Invalid credentials. Access Denied.\n");
            return false;
        }
    }
    public static void loadProductsFromFile() {
        try (BufferedReader br = new BufferedReader(new FileReader("products.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length == 4) {
                    int id = Integer.parseInt(parts[0].trim());
                    String name = parts[1].trim();
                    double price = Double.parseDouble(parts[2].trim());
                    int quantity = Integer.parseInt(parts[3].trim());
                    inventory.add(new Product(id, name, price, quantity));
                }
            }
            System.out.println("Products loaded from file successfully.\n");
        } catch (IOException e) {
            System.out.println("Error loading products from file: " + e.getMessage());
        }
    }
    public static void addProduct(Scanner scanner) {
        System.out.println("\n--- Add New Product ---");
        System.out.print("Enter Product ID: ");
        int id = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Enter Product Name: ");
        String name = scanner.nextLine();
        System.out.print("Enter Price: ");
        double price = scanner.nextDouble();
        System.out.print("Enter Stock Quantity: ");
        int quantity = scanner.nextInt();
        inventory.add(new Product(id, name, price, quantity));
        System.out.println("Product added successfully!\n");
    }
    public static void editProduct(Scanner scanner) {
        System.out.print("\nEnter Product ID to Edit: ");
        int id = scanner.nextInt();
        for (Product p : inventory) {
            if (p.id == id) {
                scanner.nextLine();
                System.out.print("Enter New Name: ");
                p.name = scanner.nextLine();
                System.out.print("Enter New Price: ");
                p.price = scanner.nextDouble();
                System.out.print("Enter New Quantity: ");
                p.quantity = scanner.nextInt();
                System.out.println("Product updated successfully!\n");
                return;
            }
        }
        System.out.println("Product not found!\n");
    }
    public static void deleteProduct(Scanner scanner) {
        System.out.print("\nEnter Product ID to Delete: ");
        int id = scanner.nextInt();
        Iterator<Product> it = inventory.iterator();
        while (it.hasNext()) {
            if (it.next().id == id) {
                it.remove();
                System.out.println("Product deleted successfully!\n");
                return;
            }
        }
        System.out.println("Product not found!\n");
    }
    public static void viewAllProducts() {
        System.out.println("\n--- Product List ---");
        System.out.printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Price", "Quantity");
        for (Product p : inventory) {
            System.out.printf("%-10d %-20s %-10.2f %-10d\n", p.id, p.name, p.price, p.quantity);
        }
        System.out.println();
    }
    public static void generateBill(Scanner scanner) {
        List<Product> cart = new ArrayList<>();
        Map<Product, Integer> quantityMap = new HashMap<>();
        scanner.nextLine();
        System.out.print("Enter Customer Name: ");
        String customer = scanner.nextLine();
        while (true) {
            System.out.print("Enter Product ID to add to bill (0 to finish): ");
            int id = scanner.nextInt();
            if (id == 0) break;
            Product selected = null;
            for (Product p : inventory) {
                if (p.id == id) {
                    selected = p;
                    break;
                }
            }
            if (selected == null) {
                System.out.println("Product not found!");
                continue;
            }
            while (true) {
                System.out.print("Enter Quantity: ");
                int qty = scanner.nextInt();
                if (qty > selected.quantity) {
                    System.out.println("Not enough stock available! Re-enter quantity.");
                } else {
                    cart.add(selected);
                    quantityMap.put(selected, qty);
                    selected.quantity -= qty;
                    System.out.println("Product added to bill.\n");
                    break;
                }
            }
        }
        if (cart.isEmpty()) {
            System.out.println("No items added. Bill not generated.\n");
            return;
        }
        double subtotal = 0;
        for (Product p : cart) {
            subtotal += p.price * quantityMap.get(p);
        }
        double gst = subtotal * 0.18;
        double discount = subtotal * 0.05;
        double total = subtotal + gst - discount;
        LocalDateTime now = LocalDateTime.now();
        String filename = "Bill_" + customer + "_" + now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HHmm")) + ".txt";
        try (FileWriter fw = new FileWriter(filename)) {
            fw.write("------------ Final Bill ------------\n");
            fw.write("Customer Name: " + customer + "\n");
            fw.write("Date: " + now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")) + "\n\n");
            fw.write(String.format("%-12s %-18s %-8s %-8s %-10s\n", "Product ID", "Product Name", "Qty", "Price", "Total"));
            fw.write("------------------------------------------------------------\n");
            for (Product p : cart) {
                int qty = quantityMap.get(p);
                double lineTotal = qty * p.price;
                fw.write(String.format("%-12d %-18s %-8d %-8.1f %-10.1f\n", p.id, p.name, qty, p.price, lineTotal));
            }
            fw.write("------------------------------------------------------------\n");
            fw.write(String.format("Subtotal:%47.1f\n", subtotal));
            fw.write(String.format("GST (18%%):%45.1f\n", gst));
            fw.write(String.format("Discount (5%%):%41.1f\n", discount));
            fw.write("------------------------------------------------------------\n");
            fw.write(String.format("Total Amount:%42.1f\n", total));
            fw.write("---------------------------------------------\n");
            fw.write("\nThank you for shopping with us!\n");
        } catch (IOException e) {
            System.out.println("Error writing bill to file.");
        }
        System.out.println("Generating bill...");
        System.out.println("Saved bill to: " + filename + "\n");
        try {
            Runtime.getRuntime().exec("notepad " + filename);
        } catch (IOException e) {
            System.out.println("Could not open the bill file automatically.");
        }
    }
}