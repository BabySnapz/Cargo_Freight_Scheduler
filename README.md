# 🚚 Cargo & Freight Scheduler

A console-based C++ scheduling system that helps streamline the assignment of cargos to freights based on location, timing, and capacity — with extensible features tailored for modern e-commerce logistics.

---

## 📌 Features

- Load freight and cargo data from `.txt` files
- Assign cargos to freights by matching:
  - Location
  - Arrival time (within 15-minute tolerance)
  - Load capacity limits
- Support for 3 freight types:
  - MiniMover – 2 cargos
  - CargoCruiser – 6 cargos
  - MegaCarrier – 12 cargos
- View matched and unmatched records
- Add/Edit/Delete freights and cargos during runtime
- Export scheduling results to any specified folder
- Operates entirely in memory; does not overwrite original input files

---

## 🧠 Freight Types

| Type         | Max Capacity |
|--------------|--------------|
| MiniMover    | 2 cargos     |
| CargoCruiser | 6 cargos     |
| MegaCarrier  | 12 cargos    |

---

## 🧭 How to Use

### 🔽 Step-by-step Instructions

1. **Start the Program**

   Run the compiled executable from your terminal or IDE.

2. **Load Input Files**

   Choose **option 1**, then paste in the path to `Freight.txt` and `Cargo.txt`.

3. **Verify Loaded Data**

   - Use **option 2** to display all freights
   - Use **option 3** to display all cargos

4. **Edit Data (Optional)**

   Use **option 6** to access the submenu for:
   - Adding
   - Editing
   - Deleting records

5. **Run Scheduling**

   Use **option 4** to match cargos to freights based on location, time, and capacity.

6. **Export the Results**

   Use **option 5**, then enter a valid folder path (e.g., `C:\Users\YourName\Desktop\Export`)

   The system will create a `Schedule.txt` file in the chosen directory.

---

## 🗂 Example Input Format

### Freight.txt

- F01 MiniMover London 0730
- F02 CargoCruiser Paris 0900
- F03 MegaCarrier Tokyo 1530

### Cargo.txt

- C01 London 0700
- C02 Paris 1720
- C03 Tokyo 1500

## 🖨 Sample Output (Schedule.txt)

### Matched Freight and Cargo Records 
| F_ID | F_Location | F_Time | C_ID | C_Location | C_Time |
|------|------------|--------|------|----------|---------|
| F01 | London | 0730 | C01 | London | 0700 |
| F03 | Tokyo | 1530 | C03 | Tokyo | 1500 |

### Unmatched Freight Records 
|F_ID | F_Location | F_Time|
|------|-----------|-------|
|F02 | Paris | 0900|

### Unmatched Cargo Records 
|C_ID | C_Location | C_Time|
|------|-----------|-------|
|C02 |Paris | 1720|



Scheduling completed.
