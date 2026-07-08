# -*- coding: utf-8 -*-
import os
import subprocess
import shutil

latex_docs_dir = "/home/swrneko/Documents/mai_shit/2lvl_2sem/letee-rabstvo/tp-deliverables/04-latex-docs"

# Mapping of classmate's directories to standard EСПД GOST PDF names
gost_mapping = {
    "Ведомость эксплуатационных документов": "gost_19.101-77.pdf",
    "Техническое задание": "gost_19.201-78.pdf",
    "Программа и методика испытаний": "gost_19.301-79.pdf",
    "Текст программы": "gost_19.401-78.pdf",
    "Описание программы": "gost_19.402-78.pdf",
    "Пояснительная записка": "gost_19.404-79.pdf",
    "Формуляр": "gost_19.501-78.pdf",
    "Описание применения": "gost_19.502-78.pdf",
    "Руководство системного программиста": "gost_19.503-79.pdf",
    "Руководство программиста": "gost_19.504-79.pdf",
    "Руководство оператора": "gost_19.505-79.pdf",
    "Спецификация": "gost_19.601-78.pdf"
}

print("Starting compilation of 12 LaTeX documents...")

for folder, gost_name in gost_mapping.items():
    folder_path = os.path.join(latex_docs_dir, folder)
    if not os.path.exists(folder_path):
        print(f"Warning: Folder {folder_path} does not exist!")
        continue
        
    print(f"\n==========================================")
    print(f"Compiling: {folder} -> {gost_name}")
    print(f"==========================================")
    
    # Run pdflatex in the document directory
    # Run twice to resolve Table of Contents, page numbers, and hyperlinks
    try:
        # First run
        print("First pass...")
        subprocess.run(
            ["pdflatex", "-interaction=nonstopmode", "main.tex"],
            cwd=folder_path,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL
        )
        
        # Second run
        print("Second pass...")
        subprocess.run(
            ["pdflatex", "-interaction=nonstopmode", "main.tex"],
            cwd=folder_path,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL
        )
        
        compiled_pdf_path = os.path.join(folder_path, "main.pdf")
        if os.path.exists(compiled_pdf_path):
            destination_path = os.path.join(latex_docs_dir, gost_name)
            shutil.copy(compiled_pdf_path, destination_path)
            print(f"Successfully compiled and copied to: {destination_path}")
        else:
            print(f"Error: compilation failed for {folder} (main.pdf not generated)")
            
    except Exception as e:
        print(f"Exception during compilation of {folder}: {e}")

    # Clean up temporary LaTeX files in the subdirectory to keep it clean
    for file in os.listdir(folder_path):
        if file.endswith((".aux", ".log", ".out", ".toc", ".nav", ".snm", ".fdb_latexmk", ".fls", ".synctex.gz")):
            try:
                os.remove(os.path.join(folder_path, file))
            except Exception:
                pass

print("\n==========================================")
print("All compilations completed!")
print("==========================================")
